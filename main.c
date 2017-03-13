#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/input.h>
#include <pthread.h>
#include <stdlib.h>

void *preUpdate();
void postUpdate();
void updatePosisi();



int main()
{
	//deklarasi variabel
	int startTime;
	int endTime;
	double elapsedTime;

	//create mobil player
	spawnPlayer();


	while(1)
	{
		startTime = clock();

		//do game stuff=======================================================
			//tangkap user-input
			if(input)
				moveObject(p,player); // move sesuai input


			//jalanin objek
			runObject();


			//kalau player collision
			if(status == 99)
				crashProcess();

			//gambar

			//cek kolisi
            checkCollision();


			//looping jalan
			if(checkRoadOutOfBound())
			{
				spawnRoad();
			}
		//====================================================================

		endTime = clock();
		elapsedTime =(double) ((double)endTime - (double)startTime);

		if(checkspawntimer())
		{
			spawnEnemy();
		}

		if(elapsedTime > 17) //biar 60fps
		{
			//do nothing
		}
		else
		{
			usleep((17-elapsedTime)*1000);
		}
	}

	return 0;
}
