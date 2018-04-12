#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<aio.h>


#define BUFFER_SIZE 1024

int MAX_LIST = 2;

int main(int argc,char **argv)
{
    //aio��������ṹ��
    struct aiocb rd;

    int fd,ret,couter;

    fd = open("test.txt",O_RDONLY);
    if(fd < 0)
    {
        perror("test.txt");
    }



    //��rd�ṹ�����
    bzero(&rd,sizeof(rd));


    //Ϊrd.aio_buf����ռ�
    rd.aio_buf = malloc(BUFFER_SIZE + 1);

    //���rd�ṹ��
    rd.aio_fildes = fd;
    rd.aio_nbytes = BUFFER_SIZE;
    rd.aio_offset = 0;

    //�����첽������
    ret = aio_read(&rd);
    if(ret < 0)
    {
        perror("aio_read");
        exit(1);
    }
	//do other things
	
    couter = 0;
//  ѭ���ȴ��첽����������
    while(aio_error(&rd) == EINPROGRESS)
    {
       // printf("��%d��\n",++couter);
    }
	
    //��ȡ�첽������ֵ
    ret = aio_return(&rd);
	
    printf("\n\n����ֵΪ:%d\n",ret);
	printf("%s\n",rd.aio_buf);
	
	free(rd.aio_buf);
	close(fd);
    return 0;
}
