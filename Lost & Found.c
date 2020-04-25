#include<stdio.h>
#include<stdlib.h>
#include<string.h>

	void admin();
	void menuadmin();
	void hapusakun();
	void user();
	void ruser();
	void luser();
	void menuuser();
	void tambahblog();
	void hapusblog();
	void editblog();
	void comment();
	void reportkomen();
	void lihatblog();


	FILE *regisuser;
	FILE *regisuser2;
	FILE *addblog;
	FILE *addblog2;
	FILE *komen;

	struct account
	{
		char user[50],pass[20];
	}r,l;

	struct blog
	{
	char nama[20],konten[500],judul[20],user[20],status[20],komen[200];
	}ab,sort[100],temp;

	int pil,i,attempt=3;
	char report[100],YN;

	main()
	{
		system("cls");
		printf("==SELAMAT DATANG DI DASKOM BLOG==\n");
		printf("1. Admin\n");
		printf("2. User\n");
		printf("3. Exit\n\n");
		printf("Silahkan Pilih : ");scanf("%d",&pil);fflush(stdin);
		switch (pil)
		{
			case 1 : admin();break;
			case 2 : user();break;
			case 3 : system("exit");break;
			default : printf("\nPilihan tersebut tidak ada\n");system("pause");main();
		}
	}

	void admin()
	{
		fflush(stdin);
		system("cls");
		char user[100],pass[100];
		
		printf("Silahkan Login\n");
		printf("\nUsername : ");gets(user);
		printf("Password : ");gets(pass);
		
		if(strcmp(user,"admin")==0 && strcmp(pass,"admin")==0)
		{
			printf("\nLogin Sukses, Silahkan tekan enter untuk lanjut\n");
			system("pause");
			menuadmin();
		}
		else
		{
			printf("\nLogin Gagal\n");
			system("pause");
			main();
		}
	}

	void menuadmin()
	{
		system("cls");
		printf("==Selamat Datang Admin==\n\n");
		printf("Menu Admin : \n");
		printf("1. Hapus Akun\n");
		printf("2. Kembali\n\n");
		printf("Silahkan Pilih : ");scanf("%d",&pil);
		switch (pil)
		{
			case 1 : hapusakun();break;
			case 2 : main();break;
			default : printf("Pilihan tersebut tidak ada");menuadmin();break;
		}
	}

	void hapusakun()
	{
    	char hapus[50];
    	
		fflush(stdin);
    	system("cls");
    	printf("LIST USER\n");
    	
		regisuser = fopen("User.dat","rb");

		i=1;
		fseek(regisuser,0,SEEK_SET);
    	while (fread(&r,sizeof(r),1,regisuser)==1)
        {
            printf( "%d. User : %s\n",i,r.user);
            i++;
        }
    	
    	printf("\nSilahkan masukkan nama yang ingin dihapus : "); 
		gets(hapus);
    	
		fseek(regisuser,0,SEEK_SET);
		i=0;
		while(fread(&r,sizeof(r),1,regisuser)!=0)
    	{
        	if(strcmp(hapus,r.user)==0)
        	{
        		i=1;break;
			}
		}
        
		if	(i==1)
		{
            printf("\nUser yang ingin dihapus ditemukan\nNama User : %s\n",hapus);
            printf("\nApakah anda yakin ingin menghapus User ? (Y/N) : ");
            scanf("%c", &YN);fflush(stdin);
            	
           	fclose(regisuser);
           	
			if(YN == 'Y' || YN == 'y')
            {
                regisuser = fopen("User.dat","rb");
                regisuser2 = fopen("User2.dat","wb");
                
				fseek(regisuser,0,SEEK_SET);
                while (fread(&r,sizeof (r),1, regisuser)==1)
                {
                   	if (strcmp(r.user,hapus)!=0)
                    {
                        fwrite(&r, sizeof(r), 1, regisuser2);
                    }
               	}
                fclose(regisuser);
                fclose(regisuser2);
                remove("User.dat");
                rename("User2.dat","User.dat");
                	
                printf("\nUser telah berhasil dihapus !\n\n");
                system("pause");
                menuadmin();
            }
            else
            {
            	printf("\nUser tidak dihapus, silahkan tekan enter\n\n");
                system("pause");
                fclose(regisuser);
                fclose(regisuser2);
                menuadmin();
            }
        }
        else
        {
            printf("User yang ingin dihapus tidak ditemukan\n\n");
            system("pause");
            fclose(regisuser);
            menuadmin();
        }
    }
		
	void user()
	{
		system("cls");
		printf("==Annyeonghaseyo==\n");
		printf("1. Registrasi\n");
		printf("2. Login\n");
		printf("3. Kembali\n\n");
		printf("Silahkan Pilih : ");scanf("%d",&pil);fflush(stdin);
		switch(pil)
		{
			case 1 : ruser();break;
			case 2 : luser();break;
			case 3 : main();break;
			default : printf("\nPilihan tersebut tidak ada\n");system("pause");user();break;
		}
	}
	
	void ruser()
	{
		system("cls");
		fflush(stdin);
		printf("Silahkan Registrasi\n");
		printf("Username	: ");gets(r.user);
		printf("Password	: ");gets(r.pass);
		
		regisuser = fopen("User.dat","ab");
		fwrite (&r,sizeof(r),1,regisuser);
		fclose(regisuser);
		
		printf("\nRegistrasi Berhasil !\n");
		system("pause");
		user();
	}
	
	void luser()
	{	
		system("cls");
		printf("Silahkan Login\n");fflush(stdin);
		printf("\nUsername : ");gets(l.user);
		printf("Password : ");gets(l.pass);
		
		regisuser = fopen("User.dat","rb");
		i=0;
		fseek(regisuser,0,SEEK_SET);
		while (fread(&r,sizeof(r),1,regisuser)!=0)
		{
			if(strcmp(l.user,r.user)==0 && strcmp(l.pass,r.pass)==0)
			{
				i=1;break;
			}
		}
		
		if (i==1)
		{
			printf("\nLogin Sukses, Silahkan tekan enter untuk lanjut\n");
			system("pause");
			menuuser();
		}
		else
		{
			attempt--;
			printf("\nLogin Gagal / Anda belum melakukan registrasi !\n");
			printf("\nSisa kesempatan anda : %d\n\n",attempt);
			system("pause");
			if (attempt==0)
			{
				attempt=3;
				user();	
			}
			else
			{
				luser();
			}
		
		}		
	}

	void menuuser()
	{
		system("cls");

		printf("==Selamat Datang %s==\n\n",l.user);
		printf("Menu User : \n");
		printf("1. Tambah Blog\n");
		printf("2. Lihat Blog\n");
		printf("3. Edit Blog\n");
		printf("4. Hapus Blog\n");
		printf("5. Comment\n");
		printf("6. Report Comment\n");
		printf("7. Kembali\n\n");
		printf("Silahkan Pilih : ");scanf("%d",&pil);
			
		switch (pil)
		{
			case 1 : tambahblog(); break;
			case 2 : lihatblog(); break;
			case 3 : editblog(); break;
			case 4 : hapusblog(); break;
			case 5 : comment(); break;
			case 6 : reportkomen(); break;
			case 7 : user(); break;
			default : 
			{
				printf("\nPilihan tersebut tidak ada\n\n");
				system("pause");
				menuuser();
				break;
			}
		}		
	}

	void tambahblog()
	{
		fflush(stdin);
		system("cls");
		printf("Nama Pengguna	: ");gets(ab.nama);
		printf("Judul		: ");gets(ab.judul);
		printf("Masukkan Konten	: \n");gets(ab.konten);
		strcpy(ab.komen,"");
		
		addblog = fopen("blog.dat","ab");
		fwrite(&ab,sizeof(ab),1,addblog);
		fclose(addblog);
		
		printf("\nBlog telah diinput\n");
		system("pause");
		menuuser();
	}
	
	void lihatblog()
	{
		i=1;
		
		system("cls");
		printf("LIST BLOG\n");
		
		addblog = fopen("blog.dat","rb");
		while (fread(&ab,sizeof(ab),1,addblog)==1)
		{
			printf("\n%d. Nama Pengguna	: %s\n",i,ab.nama);
			printf("   Judul		: %s\n",ab.judul);
			printf("   Konten		: %s\n",ab.konten);
			printf("   Komen		: %s\n",ab.komen);
			i++;	
		}
		fclose(addblog);
		system("pause");
		menuuser();	
	}
	
	void editblog()
	{
		char cari[20];
		system("cls"); 
		addblog = fopen("blog.dat","rb+"); 
		printf("LIST BLOG\n"); 
	
		i=1;
		while(fread(&ab,sizeof(ab),1,addblog)==1)
		{ 
			printf("\n%d. Nama Pengguna	: %s\n",i,ab.nama);
			printf("   Judul		: %s\n",ab.judul);
			printf("   Konten		: %s\n",ab.konten);
			printf("   Komentar		: \n%s",ab.komen);
			i++;  
		} 
  		fclose(addblog); 
  		fflush(stdin);
  		printf("\nEDIT\n");
  		printf("Masukan Judul yang akan diedit : ");gets(cari);
  		
  		addblog = fopen("blog.dat","rb+"); 
		i=0;
  		while (fread(&ab,sizeof(ab),1,addblog)==1)
  		{
  			if (strcmp(ab.judul,cari)==0)
  			{
  				i=1;break;
			}
		}
		fclose(addblog);
		
		if (i==1)
		{
			printf("\nBlog Ditemukan\n");
			printf("Nama Pengguna	: %s\n",ab.nama);
			printf("Judul		: %s\n",ab.judul);
			printf("Konten		: %s\n",ab.konten);
		
			printf("\nUbah Menjadi\n");
			printf("Nama Pengguna	: ");gets(temp.nama);
			printf("Judul		: ");gets(temp.judul);
			printf("Konten		: ");gets(temp.konten);
			
			addblog = fopen("blog.dat","rb+");
			addblog2 = fopen("blog2.dat","wb+");
			
			fseek(addblog,0,SEEK_SET);
			while (fread(&ab,sizeof(ab),1,addblog)==1)
			{
				if (strcmp(ab.judul,cari)!=0)
				{
					fwrite(&ab,sizeof(ab),1,addblog2);
				}
				else
				{
					fwrite(&temp,sizeof(temp),1,addblog2);
				}
			}
			fclose(addblog);
			fclose(addblog2);
			remove("blog.dat");
			rename("blog2.dat","blog.dat");
			
			printf("\nBlog berhasil diedit !\n");
			system("pause");
			menuuser();		
		}
		else
		{
			printf("\nBlog tidak ditemukan\n");
			system("pause");
			menuuser();
		}
	}
	
	void hapusblog()
	{ 
		system("cls"); 
		addblog = fopen("blog.dat","rb+"); 
		printf("LIST BLOG\n"); 
	
		i=1;
		while(fread(&ab,sizeof(ab),1,addblog)==1)
		{ 
			printf("\n%d. Nama Pengguna	: %s\n",i,ab.nama);
			printf("   Judul		: %s\n",ab.judul);
			printf("   Konten		: %s\n",ab.konten);
			printf("   Komentar		: %s\n",ab.komen); 
			i++;  
		} 
  		fclose(addblog); 
  
  		char hapus[100], option; 
  		
		addblog = fopen("blog.dat","rb+");  
  		printf("\n\nHAPUS\n");
  		fflush(stdin); 
  		printf("Masukan Judul Blog yang akan dihapus : "); gets(hapus); 
 
 		i=0;
 		while(fread(&ab, sizeof(ab), 1, addblog)==1) 
 		{ 
  			if(strcmp(hapus,ab.judul)==0) 
  			{ 
   				printf("\nUser yang ingin dihapus ditemukan !!\n"); 
   				printf("Nama Pengguna		: %s\n",ab.nama);
				printf("Judul			: %s\n",ab.judul);
				printf("Konten			: %s\n",ab.konten);
				printf("Komentar		: %s\n",ab.komen); 
   				i = 1; 
   				break; 
  			} 
 		} 
 		fclose(addblog); 
 
 		if (i!=1) 
 		{  
  			printf("\nBlog tidak ditemukan\n"); 
			system("pause");
			menuuser();
 		}	 
 		else 
 		{ 
  			printf("\nYakin ingin menghapus Blog tersebut (Y/N)  : "); scanf("%c", &option); fflush(stdin); 
  			if (option == 'Y' || option == 'y') 
  			{ 
   				addblog=fopen("blog.dat","rb+"); 
   				addblog2=fopen("blog2.dat","wb+"); 
   	
	   			while(fread(&ab, sizeof(ab), 1, addblog)==1) 
   				{  
    				if(strcmp(hapus,ab.judul)!=0) 
    				{ 
     					fwrite(&ab, sizeof(ab), 1, addblog2); 
    				} 
   				} 
   				fclose(addblog); 
   				fclose(addblog2); 
   				remove("blog.dat"); 
   				rename("blog2.dat","blog.dat"); 
   				printf("\nBlog tersebut berhasil dihapus !!\n");system("pause"); fflush(stdin); menuuser(); 
  			} 
  			else 
  			{ 
   				printf("\nKeluar\n"); 
				system("pause");   
				menuuser(); 
  			} 
 		}
	}

	void comment()
	{ 
		system("cls"); 
		addblog = fopen("blog.dat","rb+"); 
		
		i=1;
		printf("LIST BLOG\n"); 
		while(fread(&ab,sizeof(ab),1,addblog)==1)
		{ 
			printf("\n%d. Nama Pengguna	: %s\n",i,ab.nama);
			printf("   Judul		: %s\n",ab.judul);
			printf("   Konten		: %s\n",ab.konten);
			printf("   Komen		: %s\n",ab.komen); 
			i++; 
		} 
  		fclose(addblog); 
  
  		char edit[100];
  		addblog = fopen("blog.dat","rb+");  
  		printf("\n\nKOMEN\n");
  		fflush(stdin);
  		printf("Masukan Judul yang akan dikomen : "); gets(edit); 
		
		i=0; 
 		while(fread(&ab, sizeof(ab), 1, addblog)==1)
 		{ 
  			if (strcmp(edit,ab.judul)==0) 
  			{ 
   				i = 1; 
   				printf("\nBlog Ditemukan!!\n"); 
   				printf("Nama Pengguna		: %s\n",ab.nama);
   				printf("Judul			: %s\n",ab.judul);
   				printf("Konten			: %s\n",ab.konten);  
   				
				fseek(addblog,(int)-sizeof(ab), SEEK_CUR);
   				printf("\nMasukkan Komen:\n"); 
   				printf("Komen			: ");gets(ab.komen); 
				fflush(stdin);
   				
				fwrite(&ab, sizeof(ab), 1, addblog); 
				fclose(addblog);
   				printf("\nKomen telah di input\n"); system("pause");
   				menuuser(); 
  			} 
	 	} 
 		
		if (i==0) 
 		{ 
  			printf("\nBlog tidak ditemukan\n"); fflush(stdin); menuuser(); 
 		} 
 		fclose(addblog);
	}

	void reportkomen()
	{
		fflush(stdin);
		system("cls");
		printf("LIST BLOG\n");
		
		addblog = fopen("blog.dat","rb");
		i=1;
		while (fread(&ab,sizeof(ab),1,addblog)==1)
		{
			printf("\n%d. Nama Pengguna	: %s\n",i,ab.nama);
			printf("   Judul		: %s\n",ab.judul);
			printf("   Konten		: %s\n",ab.konten);
			printf("   Komen		: %s\n",ab.komen);
			i++;	
		}
		fclose(addblog);
		
		printf("\nREPORT\n");
		printf("Masukan komen yang ingin direport : ");
		gets(report);
		
		addblog = fopen("blog.dat","rb+"); 
		i=0;
  		while (fread(&ab,sizeof(ab),1,addblog)==1)
  		{
  			if (strcmp(ab.komen,report)==0)
  			{
  				i=1;break;
			}
		}
		fclose(addblog);
		
		if (i==1)
		{
			printf("\nKomen Ditemukan\n");
			printf("Komen		: %s\n",ab.komen);
			printf("\nApakah anda yakin ingin mereport komen ini ? (Y/N) : ");
			scanf("%c",&YN);fflush(stdin);	
			
			addblog = fopen("blog.dat","rb+");
			
			if ( YN == 'Y' || YN == 'y')
			{
				fseek(addblog,0,SEEK_SET);
				while (fread(&ab,sizeof(ab),1,addblog)==1)
				{
					if (strcmp(ab.komen,report)==0)
					{
						fseek(addblog,(long)-sizeof(ab),SEEK_CUR);
						strcpy(ab.komen,"Komentar ini telah direport oleh admin !");
						fwrite(&ab, sizeof(ab), 1, addblog);
						break;
					}
				}
				fclose(addblog);
			
				printf("\nKomen berhasil direport !\n");
				system("pause");
				menuuser();		
			}
			else
			{
				printf("\nKomen tidak direport !\n");
				system("pause");
				menuuser();
			}
		}
		else
		{
			printf("\nBlog tidak ditemukan\n");
			system("pause");
			menuuser();
		}
	}

