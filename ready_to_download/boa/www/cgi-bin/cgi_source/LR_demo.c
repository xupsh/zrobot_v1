#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

int main(void)
{
	FILE *fd;
	int num;
	char *leafName[39];

	leafName[1] ="cedrus";			leafName[2] ="Podocarpus";
	leafName[3] ="bamboo";			leafName[4] ="Nerium Indcus";
	leafName[5] ="Manglietia";		leafName[6] ="Amygdalus Persica";
	leafName[7] ="ToonaÂ Sinensis";			leafName[8] ="Sawtooth oak";
	leafName[9] ="Phoebe zhennan";			leafName[10] ="Citrus reticulata Blanco";
	leafName[11] ="Cinnamomum Japonicum";			leafName[12] ="Magnolia Grandiflora";
	leafName[13] ="Aesculus Chinensis";			leafName[14] ="Red Buckeye";
	leafName[15] ="Hibiscus";			leafName[16] ="Osmanthus Fragrans";
	leafName[17] ="Indigofera tinctoria";			leafName[18] ="Juglans mandshurica";
	leafName[19] ="Pittosporum Tobira";			leafName[20] ="oak";	//it's not a mistake,
	leafName[21] ="Prunus Yedoensis";			leafName[22] ="American Elm";
	leafName[23] ="Ginkgo Biloba";			leafName[24] ="Chinese Parasol";
	leafName[25] ="Liriodendron Chinense";			leafName[26] ="Lagerstroemia Indica";
	leafName[27] ="Mahonia Bealei";			leafName[28] ="Acer palmatum";
	leafName[29] ="Coleus";			leafName[30] ="Mulberry";
	leafName[31] ="Populus";			leafName[32] ="Cercis Chinensis";
	leafName[33] ="Brassica oleracea";			leafName[34] ="trident maple";
	leafName[35] ="KalopanaxÂ Septemlobus";			leafName[36] ="red maple";
	leafName[37] ="acer monoes";			leafName[38] ="Sibbaldia procumbens";
	leafName[0]="Please put a leaf in front of camera:) ";

	fd = fopen("state.txt", "r");

	
	if (fd < 0)
	{
		perror("open state.txt");
		exit(1);
	}
	
		printf ( "Content-type: text/html\n\n" ); 
   		printf ( "<html>\n" ); 
  		printf ( "<head>");
              
		printf (" <script> \"JavaScript\" \n");
		printf (" function myrefresh(){ \n ");
        printf (" window.location.reload();} \n");
		printf (" setTimeout('myrefresh()',500);  \n");
		printf (" </script> \n");
		
		
		printf("<title>Leaf Recognition Demo Page</title></head>\n" ); 

  		printf ( "<body>\n" ); 
  		printf ( "<div align=\"center\">\n"); 
		
        fscanf(fd,"%d",&num);

		printf("<h1>Leaf Recongntion Demo Page!</h1>");

		switch(num){
//			case 0:		printf("<img id=\"imgframe\" src=\"../0.jpg\" />"); break;
			case 1:		printf("<img id=\"imgframe\" src=\"../leaf_photo/1.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 2:		printf("<img id=\"imgframe\" src=\"../leaf_photo/2.jpg\" />");
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 3:		printf("<img id=\"imgframe\" src=\"../leaf_photo/3.jpg\" />");
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 4:		printf("<img id=\"imgframe\" src=\"../leaf_photo/4.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 5:		printf("<img id=\"imgframe\" src=\"../leaf_photo/5.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 6:		printf("<img id=\"imgframe\" src=\"../leaf_photo/6.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 7:		printf("<img id=\"imgframe\" src=\"../leaf_photo/7.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 8:		printf("<img id=\"imgframe\" src=\"../leaf_photo/8.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 9:		printf("<img id=\"imgframe\" src=\"../leaf_photo/9.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 10:		printf("<img id=\"imgframe\" src=\"../leaf_photo/10.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 11:		printf("<img id=\"imgframe\" src=\"../leaf_photo/11.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 12:		printf("<img id=\"imgframe\" src=\"../leaf_photo/12.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 13:		printf("<img id=\"imgframe\" src=\"../leaf_photo/13.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 14:		printf("<img id=\"imgframe\" src=\"../leaf_photo/14.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 15:		printf("<img id=\"imgframe\" src=\"../leaf_photo/15.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 16:		printf("<img id=\"imgframe\" src=\"../leaf_photo/16.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 17:		printf("<img id=\"imgframe\" src=\"../leaf_photo/17.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 18:		printf("<img id=\"imgframe\" src=\"../leaf_photo/18.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 19:		printf("<img id=\"imgframe\" src=\"../leaf_photo/19.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 20:		printf("<img id=\"imgframe\" src=\"../leaf_photo/20.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 21:		printf("<img id=\"imgframe\" src=\"../leaf_photo/21.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 22:		printf("<img id=\"imgframe\" src=\"../leaf_photo/22.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 23:		printf("<img id=\"imgframe\" src=\"../leaf_photo/23.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 24:		printf("<img id=\"imgframe\" src=\"../leaf_photo/24.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 25:		printf("<img id=\"imgframe\" src=\"../leaf_photo/25.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 26:		printf("<img id=\"imgframe\" src=\"../leaf_photo/26.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 27:		printf("<img id=\"imgframe\" src=\"../leaf_photo/27.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 28:		printf("<img id=\"imgframe\" src=\"../leaf_photo/28.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 29:		printf("<img id=\"imgframe\" src=\"../leaf_photo/29.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 30:		printf("<img id=\"imgframe\" src=\"../leaf_photo/30.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 31:		printf("<img id=\"imgframe\" src=\"../leaf_photo/31.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 32:		printf("<img id=\"imgframe\" src=\"../leaf_photo/32.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 33:		printf("<img id=\"imgframe\" src=\"../leaf_photo/33.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 34:		printf("<img id=\"imgframe\" src=\"../leaf_photo/34.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 35:		printf("<img id=\"imgframe\" src=\"../leaf_photo/35.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 36:		printf("<img id=\"imgframe\" src=\"../leaf_photo/36.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 37:		printf("<img id=\"imgframe\" src=\"../leaf_photo/37.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;
			case 38:		printf("<img id=\"imgframe\" src=\"../leaf_photo/38.jpg\" />"); 
					printf("<h3>  %s</h3>",leafName[num]);break;

			default:	printf("<img id=\"imgframe\" src=\"../leaf_photo/0.jpg\" />");
					printf("<h3>Please put a leaf in front of camera %s</h3>",leafName[num]);break;
		}
		
		printf("<h2>The number of identifiable images is :%d</h2>",num);
	//	printf ("<h1><a href=http://192.168.1.100/index.html>·µ»ØÖ÷Ò³</a>\n</h1>");
		printf ("<a href=/home.html>Back to home page</a>\n");
		printf ("</div>");
		printf ( "<body>\n" ); 
   		printf ( "</html>\n" ); 
	
		fclose(fd);
		return 0;
}
