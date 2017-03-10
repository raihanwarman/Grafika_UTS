#include <time.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	//deklarasi variabel
	int startTime;
	int endTime;
	double elapsedTime;

	//create mobil player
	spawnPlayer();
	spaw


	while(1)
	{
		startTime = clock();

		//do game stuff=======================================================
			//tangkap user-input
			if(input)
				moveObject(sesuaiInput);


			//jalanin objek
			runObject();


			//kalau player collision
			if(status == 99)
				crashProcess();

			//gambar

			//cek kolisi
			if(checkCollision())
				startCrash();

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