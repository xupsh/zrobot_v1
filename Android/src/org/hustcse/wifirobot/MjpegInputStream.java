package org.hustcse.wifirobot;

import java.io.BufferedInputStream;
import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class MjpegInputStream extends DataInputStream {
	
	//SOI is the start of image marker and  contains the marker code values FFh D8h
	//EOF is the end of image marker  and  contains the marker code valuse FFh D9h
	private final byte[] SOI_MARKER = { (byte) 0xFF, (byte) 0xD8 };
	private final byte[] EOF_MARKER = { (byte) 0xFF, (byte) 0xD9 };
	
	//make the data content lenght
	private final String CONTENT_LENGTH = "Content-Length";
	
	//define the MAXLENGHT
	private final static int HEADER_MAX_LENGTH = 100;
	private final static int FRAME_MAX_LENGTH = 40000 + HEADER_MAX_LENGTH;
	public int mContentLength = -1;
	
	//Destructor
	public MjpegInputStream(InputStream in) {
		super(new BufferedInputStream(in, FRAME_MAX_LENGTH));
	}
	
	/**
	 * To cheak the end of a frame picture
	 * @param in DataIutStream
	 * @param sequence the marker of to cheak
	 * @return the position of the end of the sequence
	 * @throws IOException
	 */
	private int getEndOfSeqeunce(DataInputStream in, byte[] sequence) throws IOException {
		int seqIndex = 0;
		byte c;
		for(int i=0; i < FRAME_MAX_LENGTH; i++) {
			c = (byte) in.readUnsignedByte();
			if(c == sequence[seqIndex]) {
				seqIndex++;
				if(seqIndex == sequence.length) {
					return i + 1;
				}
			} else {
				seqIndex = 0;
			}
		}
		return -1;
	}
	/**
	 * To cheak the start of a frame picture
	 * @param in
	 * @param sequence
	 * @return
	 * @throws IOException
	 */
	private int getStartOfSequence(DataInputStream in, byte[] sequence) throws IOException {
		int end = getEndOfSeqeunce(in, sequence);
		return (end < 0) ? (-1) : (end - sequence.length);
	}
	
	/**
	 * To get the lenght of the picture
	 * @param headerBytes
	 * @return the lenght of the picture
	 * @throws IOException
	 * @throws NumberFormatException
	 */
	private int parseContentLength(byte[] headerBytes) throws IOException, NumberFormatException {
		ByteArrayInputStream headerIn = new ByteArrayInputStream(headerBytes);
		Properties props = new Properties();
		props.load(headerIn);
		return Integer.parseInt(props.getProperty(CONTENT_LENGTH));
	}   
	
	/**
	 * Decode the jpeg format to bitmap
	 * @return
	 * @throws IOException
	 */
	public byte[] readMjpegFrame() throws IOException {
		
		mark(FRAME_MAX_LENGTH);
		int headerLen = getStartOfSequence(this, SOI_MARKER);
		reset();
		byte[] header = new byte[headerLen];
		//Read the header
		readFully(header);
		try {
			//get the lenght of a frame of picture
			mContentLength = parseContentLength(header);
		} catch (NumberFormatException nfe) { 
			nfe.getStackTrace();
			mContentLength = getEndOfSeqeunce(this, EOF_MARKER); 
		}
		//reset
		reset();
		byte[] frameData = new byte[mContentLength];
		//skip the head
		skipBytes(headerLen);
		//read the picture
		readFully(frameData);
		//decode
		return frameData;
	}
}
