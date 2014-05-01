#/bin/sh!
cvlc -vvv v4l2:// :v4l2-vdev="/dev/video0" --sout '#transcode{vcodec=x264{keyint=60,idrint=2},vcodec=h264,vb=400,width=368,heigh=208,acodec=mp4a,ab=32 ,channels=2,samplerate=22100}: standard{access=http,mux=asf,dst=127.0.0.1:8080}' --no-sout-audio
