#include <stdlib.h>
#include <ringbuf.h>
#include <conio.h>

#define N	0x400

int main(){
	// 1024 элемента uint16_t
	static uint8_t		data[ rbSize(N,sizeof(uint16_t)) ];
	//
	tRingBuffer	rb;
	uint16_t	c;
	uint16_t	i;
	//
	ccls(016);
	//
	printf("Ringbuf Test.\n\n");
	ringBufferInit(&rb, data, sizeof(data));
	printf("Create %i bytes, %i elements\n\n",sizeof(data), N);
	
	i=0;
	while( ringBufferWrite(&rb,&i,sizeof(i)) ){i++;}
	printf("Write %i bytes to full.\n\n",i);
	i=0;
	while( ringBufferWrite(&rb,&i,sizeof(i)) ){i++;}
	printf("Write %i bytes to full.\n\n",i);
	
	i=0;
	while( ringBufferRead(&rb,&c,sizeof(c)) ){
		if( i!=c ){
			printf("Error on read %i element.\n",i);
			break;
		}
		i++;
	}
	printf("Read %i bytes to empty.\n\n",i);
	
	i=0;
	while( ringBufferRead(&rb,&c,sizeof(c)) ){
		if( i!=c ){
			printf("Error on read %i element.\n",i);
			break;
		}
		i++;
	}
	printf("Read %i bytes to empty.\n\n",i);
	
	printf("Ok\n",i);
	
	
	while(1){}
	return 0;
}
