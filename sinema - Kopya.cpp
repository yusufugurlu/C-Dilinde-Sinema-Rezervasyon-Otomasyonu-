#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include <iostream>
#include<unistd.h>


//Tarih göstermek için kullanýllan metod
void TarihGoster()
{
	
  time_t simdiki_zaman; 
   time(&simdiki_zaman);
	struct tm *zaman=localtime(&simdiki_zaman);
   char *Tarih;
  
printf("\t\t\t\t\t\tTarih: %d.%d.%d",zaman->tm_mday,zaman->tm_mon,zaman->tm_year+1900);	

}

//Burda ise metodlarý tanýmlamalar yapýldý.
void AnaIslem();
void OdemeYeri(int SeansId,int FilmId,int SalonId,int KullaniciId);
void BlokeGuncelleme(int Durum,int Id);
void Rezervasyon();
void SeansSecimi(int Id,int FilmId);
void YorumYap();
void KullaniciIslemleri();
// structlar olusturuldu. 
struct Bilet{
	int Id;
	int KullaniciId;
	int FilmId;
	int KoltukId;
	int SalonId;
	int SeansId;
	
};
struct Yorumlar{
	int Id;
	int FilmId;
	int KullaniciId;
	char Yorum[1000];
	
};

struct Kullanici{
int Id;
char Adi[100];
char Soyad[100];
char Sifre[100];
char Ipucu[20];	
char KullaniciAdi[100];
char Telefon[100];
char eposta[100];
int Durum;
};

struct Tur{
  int Id;
  char Adi[100]; 		
}; 

struct Filmler{
   int Id;
   char Adi[100];
   int FTuru;
   char FYonetmeni[100];
   int Saati;	
}; 

struct Salon{
	int Id;
	char Adi[100];
	int FId;	
};

struct Seans{
  int Id;	
  char SeSaati[100];		
};

struct Koltuk
{
int Id;	
int SalonID;
char KoltukNo[3];
int Durum;	
};

struct SalonSeans
{
int SalonId;
int SeansId;
char Tarih[11];		
};

//Burda structlardan dizi seklinde tanýmlamalar yapýldý.
//Kaç tane öðe oldugunu belirtmek için index artýrýcý burada tanýmlamalar yapýldý.
int DurumId=-1;
struct Yorumlar YYorum[100];
struct Bilet BBilet[100];
struct Kullanici KKullanici[100];
struct Koltuk KKoltuk[100];
struct Salon SSalon[100];
struct Seans SSeans[100];
struct Filmler FFilmler[100];
struct Tur TTurler[100];
struct SalonSeans SSalonSeans[100];
int TurSayisi=0;
int SalonSayisi=0;
int SeansSayisi=0;
int KoltukSayisi=0;
int FilmSayisi=0;
int SalonSeansSayisi=0;
int KullaniciSayisi=0;
int BiletSayisi=0;
int YorumSayisi=0;
int YorumDurumId=0;


//Biletleri caðýrma, islemi bilet.txt verileri BBilet structa atýyoruz.
void BiletleriCagir()
{
	
FILE *fp;
char cDosyaAdi[100] ="Bilet.txt";
if((fp=fopen(cDosyaAdi,"r"))== NULL)
{
	printf("Dosya acilamadi.");
}

else
{
      while(!feof(fp))
      {
		fscanf(fp,"%d %d %d %d %d %d\n",&BBilet[BiletSayisi].Id,&BBilet[BiletSayisi].KullaniciId,&BBilet[BiletSayisi].FilmId,&BBilet[BiletSayisi].KoltukId,&BBilet[BiletSayisi].SalonId,&BBilet[BiletSayisi].SeansId);
		BiletSayisi++;
   
	  }
	fclose(fp);
}	
}


//FilmYorumlar.txt verileri YYorum struct dizine atýldý.
void YorumlariCagir()
{
	
FILE *fp;
char cDosyaAdi[100] ="FilmYorumlari.txt";
if((fp=fopen(cDosyaAdi,"r"))== NULL)
{
	printf("Dosya acilamadi.");
}

else
{
      while(!feof(fp))
      {
		fscanf(fp,"%d %d %d %s\n",&YYorum[YorumSayisi].Id,&YYorum[YorumSayisi].FilmId,&YYorum[YorumSayisi].KullaniciId,YYorum[YorumSayisi].Yorum);
		YorumSayisi++;
   
	  }
	fclose(fp);
}	
}


//Kullanicilar.txt KKullanicilar struct dizisine atadýk.
void KullaniciCagir()
{
	
FILE *fp;
char cDosyaAdi[100] ="Kullanicilar.txt";
if((fp=fopen(cDosyaAdi,"r"))== NULL)
{
	printf("Dosya acilamadi.");
}

else
{
      while(!feof(fp))
      {
		fscanf(fp,"%d %s %s %s %s %s %s %s %d\n",&KKullanici[KullaniciSayisi].Id,KKullanici[KullaniciSayisi].Adi,KKullanici[KullaniciSayisi].Soyad,KKullanici[KullaniciSayisi].KullaniciAdi,KKullanici[KullaniciSayisi].Telefon,KKullanici[KullaniciSayisi].eposta,KKullanici[KullaniciSayisi].Sifre,KKullanici[KullaniciSayisi].Ipucu,&KKullanici[KullaniciSayisi].Durum);
		KullaniciSayisi++;
   
	  }
	fclose(fp);
}	
}

//Tur.txt alýnan veriler TTurler struct atandý.
void TurleriCagir()
{
	
FILE *fp;
char cDosyaAdi[100] ="Tur.txt";
if((fp=fopen(cDosyaAdi,"r"))== NULL)
{
	printf("Dosya acilamadi.");
}

else
{
      while(!feof(fp))
      {
		fscanf(fp,"%d %s\n",&TTurler[TurSayisi].Id,TTurler[TurSayisi].Adi);
		TurSayisi++;
   
	  }
	fclose(fp);
}	
}

//Salon.txt alýnan veriler SSalon struct atandý.
void SalonlariCagir()
{
	
FILE *fp;
char cDosyaAdi[100] ="Salon.txt";
if((fp=fopen(cDosyaAdi,"r"))== NULL)
{
	printf("Dosya acilamadi.");
}

else
{
      while(!feof(fp))
      {
		fscanf(fp,"%d %s %d\n",&SSalon[SalonSayisi].Id,SSalon[SalonSayisi].Adi,&SSalon[SalonSayisi].FId);
		SalonSayisi++;
   
	  }
	fclose(fp);
}	
}

//Seans.txt verileri SSeans struct atandý.
void SeanslariCagir()
{
	
FILE *fp;
char cDosyaAdi[100] ="Seans.txt";
if((fp=fopen(cDosyaAdi,"r"))== NULL)
{
	printf("Dosya acilamadi.");
}

else
{
      while(!feof(fp))
      {
		fscanf(fp,"%d %s\n",&SSeans[SeansSayisi].Id,SSeans[SeansSayisi].SeSaati);
		SeansSayisi++;
   
	  }
	fclose(fp);
}	
}

//Koltuk.txt alýnan veriler KKoltuk struct atandý.
void KoltuklariCagir()
{
FILE *fp;
char cDosyaAdi[100] ="Koltuk.txt";
if((fp=fopen(cDosyaAdi,"r"))== NULL)
{
	printf("Dosya acilamadi.");
}

else
{
      while(!feof(fp))
      {
		fscanf(fp,"%d %d %s %d\n",&KKoltuk[KoltukSayisi].Id,&KKoltuk[KoltukSayisi].SalonID,KKoltuk[KoltukSayisi].KoltukNo,&KKoltuk[KoltukSayisi].Durum);
		KoltukSayisi++;
   
	  }
	fclose(fp);
}
	
	
}

//SalonSeans.txt alýnan veriler SSalonSeans struct atandý.
void SalonSeansCagir()
{
FILE *fp;
char cDosyaAdi[100] ="SalonSeans.txt";
if((fp=fopen(cDosyaAdi,"r"))== NULL)
{
	printf("Dosya acilamadi.");
}

else
{
      while(!feof(fp))
      {
		fscanf(fp,"%d %d %s\n",&SSalonSeans[SalonSeansSayisi].SalonId,&SSalonSeans[SalonSeansSayisi].SeansId,SSalonSeans[SalonSeansSayisi].Tarih);
		SalonSeansSayisi++;
   
	  }
	fclose(fp);
}
	
	
}

//Filmler.txt alýnan veriler FFilmler.txt struct atandý.
void FilmleriCagir()
{
FILE *fp;
char cDosyaAdi[100] ="Filmler.txt";
if((fp=fopen(cDosyaAdi,"r"))== NULL)
{
	printf("Dosya acilamadi.");
}

else
{
      while(!feof(fp))
      {
		fscanf(fp,"%d  %s  %d  %s  %d\n",&FFilmler[FilmSayisi].Id,FFilmler[FilmSayisi].Adi,&FFilmler[FilmSayisi].FTuru,FFilmler[FilmSayisi].FYonetmeni,&FFilmler[FilmSayisi].Saati);
		FilmSayisi++;
   
	  }
	fclose(fp);
}
	
	
}


void IdGoreTurGetir(int Id){
//ID'e göre filmin turunu getirir.Rezervasyondan çaðýrýlýyor.
for(int i=0;i<TurSayisi;i++)	
{
  if(TTurler[i].Id==Id)	
	{
printf("\nTuru : %s\n",TTurler[i].Adi);		
	 break;
	}
	
}	

}

int IdGoreFilmGetir(int Id){
//Burda ise rezervasyonda film seçme islemi yapýldýktan sonra gonderilen ID Filmler.txt bulunuyor mu diye.	
int deger=-1;
for(int i=0;i<FilmSayisi;i++)	
{
  if(FFilmler[i].Id==Id)	
	{
printf("Filmin Adi:%s\n",FFilmler[i].Adi);	
    deger=1;	
	 break;
	}
	
}	
return deger;
}

int IdGoreFilmGetir2(int Id){

int deger=-1;
if(Id==999)
{
sleep(3);
return 999;
}


for(int i=0;i<SalonSayisi;i++)	
{
  if(SSalon[i].Id==Id)	
	{
	
   return SSalon[i].FId;
	 break;
	}
	
}	
return deger;
}

void IdGoreSeansGetir(int Id){

// Burda salonun hangi seanslarý varsa çaðýrýyoruz..
for(int i=0;i<SeansSayisi;i++)	
{
  if(SSeans[i].Id==Id)	
	{
	
   printf("\nSeans Id: %d",SSeans[i].Id);
   printf("\nSeans Saati: %s",SSeans[i].SeSaati);
   break;
	}
	
}	

}

int IdGoreSeansGetir2(int Id){
	int deger=-1;
	if(Id==999)
	{
		sleep(3);
		return 999;
	}
for(int i=0;i<SalonSeansSayisi;i++)	
{

  if(SSalonSeans[i].SeansId==Id)	
	{
	
	deger= SSalonSeans[i].SeansId;
     break;    
 
	}
	
	
}
return deger;	

}

void FilminOzellikleri(int SeansId,int FilmId,int SalonId)
{
	system("cls");		
printf("\tSINEMA OTOMASYONUNA HOSGELDINIZ\n");	
printf("KOLTUK SECIMINE HOSGELDINIZ \n");
TarihGoster();

printf("\nSalon Adi:%s\n",SSalon[SalonId].Adi);
printf("\nFilmin Adi : %s",FFilmler[FilmId].Adi);
IdGoreTurGetir(FFilmler[FilmId].FTuru);
printf("Filmin yonetmeni: %s\n",FFilmler[FilmId].FYonetmeni);
printf("Filmin suresi: %d.dk",FFilmler[FilmId].Saati);
}


void FilminOzellikleri2(int SeansId,int FilmId,int SalonId,int kullaniciId)
{
system("cls");		
printf("\tSINEMA OTOMASYONUNA HOSGELDINIZ\n");	
printf("KOLTUK SECIMINE HOSGELDINIZ \n");
TarihGoster();
printf("\nKullanicinin Adi ve soyadi:%s %s",KKullanici[kullaniciId].Adi,KKullanici[kullaniciId].Soyad);
printf("\nSalon Adi:%s\n",SSalon[SalonId].Adi);
printf("\nFilmin Adi : %s",FFilmler[FilmId].Adi);
IdGoreTurGetir(FFilmler[FilmId].FTuru);
printf("Filmin yonetmeni: %s\n",FFilmler[FilmId].FYonetmeni);
printf("Filmin suresi: %d.dk",FFilmler[FilmId].Saati);
}

int IdGoreKoltukGetir(char No[100],int SalonNo){
for(int i=0;i<KoltukSayisi;i++)	{
	
if(strcmp(KKoltuk[i].KoltukNo,No)==0 && KKoltuk[i].SalonID==SalonNo){
return KKoltuk[i].Id;
break;	
}	
	
}
	
	
}

int IdGoreKullaniciGetir(char No[100]){
for(int i=0;i<KullaniciSayisi;i++)	{
	
if(strcmp(KKullanici[i].KullaniciAdi,No)==0 || strcmp(KKullanici[i].Telefon,No)==0){
return KKullanici[i].Id;
break;	
}	
	
}
	
	
}





int KoltukKontrol(char KoltukNo[100],int SalonID)
{
	int deger=-1;
	for(int i=0;i<KoltukSayisi;i++)
	{
		if(KKoltuk[i].SalonID==SalonID)
		{
			if(strcmp(KKoltuk[i].KoltukNo,KoltukNo)==0)
			{
				if(KKoltuk[i].Durum==1)
				{
					return 1;
		            break;		
				}
				
			}
		
			
		}
		
	}
	return deger;
	
}




void OdemeYeri(int SeansId,int FilmId,int SalonId,int KullaniciId)
{
if(KullaniciId==-1)
{
KullaniciId=DurumId-1;
}
FilminOzellikleri2(SeansId,FilmId,SalonId,KullaniciId);
int sayac=0;
printf("\n---------------PERDE-----------------------\n");
for(int i=0;i<KoltukSayisi;i++)	
{
  if(KKoltuk[i].SalonID==SalonId+1) 	
  {
  		int Deger3=0;
  	for(int j=0;j<BiletSayisi;j++)
  	{
  		int Deger2=0;
  	  if(KKoltuk[i].Durum==1)
  	  {
  	  
  	  		printf("%s(X) ",KKoltuk[i].KoltukNo);
  	  	
  	         Deger3=1;
         	break;
  	
     	}
		
	}
	if(Deger3!=1)
	{
		 		printf("%s(+) ",KKoltuk[i].KoltukNo);
	}
 
  	if(sayac>5)
  	{
  		printf("\n");
  		sayac=0;
	  }
	  else
	  sayac++;
   }
   else
   printf("");

	
}
Git2:
int secim2;
int RezerveKoltuk=0;
char KullaniciAdi[100];
char Sifre[100];
int Ogrenci=0;

printf("\n\n X gosterilenler dolu - + gosterilenler ise bos oldugunu gosterir.\n");	
printf("FIYAT LISTESI: OGRENCI 8 TL - TAM 14 TL DIR. ");
printf("\nKac tane koltuk rezervasyon etmek istiyorsunuz: ");	
scanf("%d",&RezerveKoltuk);	
int Kontrol1[11]={0,1,2,3,4,5,6,7,8,9};
int Sayac1=0;
for(int j=0;j<11;j++)
{
	if(RezerveKoltuk==Kontrol1[j])
	{
		Sayac1++;
	}
}
if(sayac==0)
{
	printf("\nGecersiz Islem");
	goto Git2;
}
char RezerveKoltukDizi[RezerveKoltuk][100];
char x[100];
//int iRezerveKoltuk[RezerveKoltuk];
int i=0;
while(i<RezerveKoltuk)
{
	printf("Koltuk No giriniz: ");
	scanf("%s",x);
	int a=0;
	a=KoltukKontrol(x,SalonId+1);
	if(a==-1)
	{
			strcpy(RezerveKoltukDizi[i],x);
			printf("%s\n",RezerveKoltukDizi[i]);
			i++;			
	}
	else if(a==1)
	{
		printf("Yazdiginiz konum doludur.");
	}

}
char karar[2];
printf("Ogrenci varsa kac tane ogrenci oldugunu yaziniz: ");
scanf("%d",&Ogrenci);
int Toplam=0;
Toplam=(Ogrenci*8)+(14*(RezerveKoltuk-Ogrenci));
printf("Toplam odemeniz : %d TL ",Toplam);
bas:
printf("\n rezervasyon yapilsin mi[y/n]: ");
scanf("%s",karar);
if(strcmp(karar,"y")==0 || strcmp(karar,"Y")==0 )
{
char cDosyaAdi2[100] ="Koltuk.txt";
remove(cDosyaAdi2);
 FILE *fp5,*fp6;
fp5=fopen(cDosyaAdi2,"a");
fclose(fp5);
fp6=fopen(cDosyaAdi2,"a");

for(int i=0;i<KoltukSayisi;i++)
{
	for(int j=0;j<RezerveKoltuk;j++)
	{
	if(strcmp(KKoltuk[i].KoltukNo,RezerveKoltukDizi[j])==0 )
	{
	if(KKoltuk[i].SalonID==SalonId+1)
		{
			KKoltuk[i].Durum=1;
		}
		break;
	}	
		
	}
}
for(int i=0;i<KoltukSayisi;i++)
{
	fprintf(fp6,"%d %d %s %d\n",KKoltuk[i].Id,KKoltuk[i].SalonID,KKoltuk[i].KoltukNo,KKoltuk[i].Durum);
}
fclose(fp6);


	FILE *fp;
	char cDosyaAdi[100] ="Bilet.txt";
if((fp=fopen(cDosyaAdi,"a"))== NULL)
{

printf("Dosya acilamadi.");

}

else
{

for(int i=0;i<RezerveKoltuk;i++)
{
	int koltukId=0;
	koltukId= IdGoreKoltukGetir(RezerveKoltukDizi[i],SalonId+1);
	fprintf(fp,"%d %d %d %d %d %d\n",BiletSayisi,KullaniciId+1,FilmId+1,koltukId,SalonId+1,SeansId);
}
    

	fclose(fp);

}
FILE *fp2;
fp2=fopen("BiletSatis.txt","a");
fprintf(fp2,"%d %d\n",BiletSayisi,Toplam);
fclose(fp2);
int x;
printf("Filmi izledikten sonra yorum yapmayi unutmayin... :)\n");
don:
printf("Ana ekran gitmek icin 1 e basýn - cikis icin 0 basin: ");
scanf("%d",&x);	
if(x==1)
AnaIslem();
else if(x==0) exit(1);
else
{
	printf("gecersiz islem "); sleep(3); goto don;
}
 
}

else if(strcmp(karar,"n")==0 || strcmp(karar,"N")==0 ){
printf("Ana menu geri donuluyor...");
sleep(3);
AnaIslem();
}

else
{
printf("gecersiz islem ");
sleep(3);
goto bas;	
	
}
}




int KullaniciGirisi(char kullaniciAdi[100],char Sifre[100])
{
	int deger=-1;
	int deger2=-1;
for(int i=0;i<KullaniciSayisi;i++){
	
	if(strcmp(kullaniciAdi,KKullanici[i].KullaniciAdi)==0 ||strcmp(kullaniciAdi,KKullanici[i].Telefon)==0)
	  {
	  	 deger=i;
	  	
	  }
	  
	   
	
if((strcmp(kullaniciAdi,KKullanici[i].KullaniciAdi)==0 ||strcmp(kullaniciAdi,KKullanici[i].Telefon)==0) && strcmp(Sifre,KKullanici[i].Sifre)==0 )	
	{
       deger2=i;
		break;
	}
	
}
if(deger==-1)
return 99;
else
{
	return deger2;
}
	
}


int  KullaniciOlustur()
{
int Id;
char KullaniciAdi[100];
char Adi[100];
char Soyad[100];
char Eposta[100];
char Telefon[100];
char Sifre[100];
char Ipucu[100];	
system("cls");	
printf("KULLANICI OLUSTURMA  \n");
KullaniciSayisi++;
Id=KullaniciSayisi;
printf("Adinizi giriniz: ");
scanf("%s",Adi);
printf("Soyadinizi giriniz: ");
scanf("%s",Soyad);
printf("Kullanici adi giriniz: ");
scanf("%s",KullaniciAdi);
printf("Eposta giriniz: ");
scanf("%s",Eposta);
printf("telefon giriniz: ");
scanf("%s",Telefon);
printf("Sifre giriniz: ");
scanf("%s",Sifre);
printf("Ipucu giriniz: ");
scanf("%s",Ipucu);
		FILE *fp;

	

	char cDosyaAdi[100] ="Kullanicilar.txt";
if((fp=fopen(cDosyaAdi,"a"))== NULL)
{

printf("Dosya acilamadi.");

}

else
{

    fprintf(fp,"%d %s %s %s %s %s %s %s %d\n",Id,Adi,Soyad,KullaniciAdi,Telefon,Eposta,Sifre,Ipucu,0);

	fclose(fp);
	KullaniciSayisi=0;
	KullaniciCagir();
}	

return 1;
sleep(3);	
}

void KoltukSecimi(int SeansId,int FilmId,int SalonId)
{
//DurumID farklý ise Odeme alanýna gitsin.	
if(DurumId!=-1)
{
OdemeYeri(SeansId,FilmId,SalonId,-1);	
}
else
{
basadon:	
FilminOzellikleri(SeansId,FilmId,SalonId);
int sayac=0;
printf("\n---------------PERDE-----------------------\n");
for(int i=0;i<KoltukSayisi;i++)	
{
  if(KKoltuk[i].SalonID==SalonId+1) 	
  {
  	for(int j=0;j<BiletSayisi;j++)
  	{
  	  if(KKoltuk[i].Id==BBilet[j].KoltukId)
  	  {
  	  
  	  		printf("%s(X) ",KKoltuk[i].KoltukNo);
  	  	
  	
         	break;
  	
     	}
		
	}
	
  		printf("%s(+) ",KKoltuk[i].KoltukNo);
  	if(sayac>5)
  	{
  		printf("\n");
  		sayac=0;
	  }
	  else
	  sayac++;
   }
   else
   printf("");

	
}
printf("\nLutfen oturum aciniz..\n");
int Secim2=0;
Tekrar:
printf("1-KullaniciIslemlerine git\n2-Ana menu\nIslem seciniz: ");
scanf("%d",&Secim2);
switch (Secim2)
{
case 1:	KullaniciIslemleri(); break;
case 2:AnaIslem(); break;
default:printf("Yanlis girdiniz.\n");goto Tekrar; break; 

}	
}	
	
	
}

void SeansSecimi(int Id,int FilmId){
int secim;
char AdSoyad[100]="";	
//Burdaki durumID Kullanýcý menusunden giriþ yapýldýysa login olup adý ve soyadinin çýkmasýný saðladýk.
if(DurumId!=-1)
{
strcat(AdSoyad,KKullanici[DurumId-1].Adi);
strcat(AdSoyad," ");
strcat(AdSoyad,KKullanici[DurumId-1].Soyad);
	
}
	
system("cls");		
printf("\tSINEMA OTOMASYONUNA HOSGELDINIZ\n");	
printf("SEANS SECIMINE HOSGELDINIZ \n");
TarihGoster();
printf("\nKisinin adi ve soyadi: %s",AdSoyad);
//Filmiin hangi salonda oldugunu gösterir.
printf("\nSalon Adi:%s\n",SSalon[Id-1].Adi);
printf("\nFilmin Adi : %s",FFilmler[FilmId-1].Adi);
IdGoreTurGetir(FFilmler[FilmId-1].FTuru);
printf("Filmin yonetmeni: %s\n",FFilmler[FilmId-1].FYonetmeni);
printf("Filmin suresi: %d",FFilmler[FilmId-1].Saati);
printf("\n--------------------------------------");
for(int i=0;i<SalonSeansSayisi;i++)
{
	if(SSalonSeans[i].SalonId==Id)
	{
		IdGoreSeansGetir(SSalonSeans[i].SeansId);
		
		
	}
}
git2:
printf("\ngeri donmek icin 999 basin..");	
printf("\nLutfen Seansin Id no giriniz: ");	
scanf("%d",&secim);
//Burda kontrol ediyoruz girilen deger uusuyor mu .
int Kontrol=IdGoreSeansGetir2(secim);
switch(Kontrol)
{
case -1: printf("Gecersiz islem "); sleep(3); goto git2; break; 
case 999: Rezervasyon(); break;	
default: KoltukSecimi(Kontrol,FilmId-1,Id-1);	
}	
	
	
}
void Rezervasyon()
{
//Kullancinin login olmus mu olmamýs mý oldugunu kontrol ediyoruz.	
char AdSoyad[100]="";	
if(DurumId!=-1)
{
strcat(AdSoyad,KKullanici[DurumId-1].Adi);
strcat(AdSoyad," ");
strcat(AdSoyad,KKullanici[DurumId-1].Soyad);
	
}

	

char FilmAdi[100];
int secim;	
//Burda ise vizyondaki filmleri goruntuler
system("cls");		
printf("\tSINEMA OTOMASYONUNA HOSGELDINIZ\n");	
printf("SALON SECIMINE HOSGELDINIZ \n");
TarihGoster();	
printf("\nKisinin Adi ve soyadi %s",AdSoyad);
for(int i=0;i<SalonSayisi;i++)
{	
printf("\nID: %d\n",SSalon[i].Id);	
printf("Salon Adi: %s\n",SSalon[i].Adi);	
IdGoreFilmGetir(SSalon[i].FId);	
printf("\n-----------------");
}
printf("\ngeri donmek icin 999");
git:
printf("\nLutfen istediginiz Salon Id girin(Id yanindaki degerler.): ");
scanf("%d",&secim);	
int x= IdGoreFilmGetir2(secim);
switch(x){
case -1: printf("\nGecersiz islem "); sleep(3); goto git; break; 	
case 999: AnaIslem();
default: 	SeansSecimi(secim,x);  break;	

}
}

void RezervasyonIptal()
{
	system("cls");
	if(DurumId==-1)
	{
		printf("Lutfen oturum acin. \n");
		printf("Kullanici islemlerine yonlendiriliyor.");
		sleep(3);
	  KullaniciIslemleri();		
	}
	else
	{
	system("cls");		
printf("\tSINEMA OTOMASYONU\n");	
printf("Rezervasyon Iptal \n");		

for(int i=0;i<KullaniciSayisi;i++)			
{
if(KKullanici[i].Id==DurumId)
	{
		printf("Sayin %s %s",KKullanici[i].Adi,KKullanici[i].Soyad);
	}
}
printf("\n---------------------------------------\n");

for(int i=0;i<BiletSayisi;i++)
	{
		if(DurumId==BBilet[i].KullaniciId)
		{
		
			printf("(%d)ID \n",BBilet[i].Id);
			IdGoreFilmGetir(BBilet[i].FilmId);
				for(int j=0;j<SalonSayisi;j++)
			{
				if(BBilet[i].SalonId==SSalon[j].Id)
				{
					printf("Salon Adi : %s\n",SSalon[j].Adi);
				}
				
			}
			
			for(int j=0;j<SeansSayisi;j++)
			{
				if(BBilet[i].SeansId==SSeans[j].Id)
				{
					printf("Seans Saati : %s\n",SSeans[j].SeSaati);
				}
				
			}
			
			for(int j=0;j<KoltukSayisi;j++)
			{
				if(KKoltuk[j].Id==BBilet[i].KoltukId)
				{
					printf("\nKoltuk No: %s\n",KKoltuk[j].KoltukNo);
				}
			}
		}
		printf("\n-------------------------------------\n");
	}
	
	printf("ID ve Koltuk No silmek istediginizi yaziniz: ");
	
//}			
	}
	
	
	
}
void BlokeGuncelleme(int Durum,int Id)
{
	remove("Kullanicilar.txt"); 
	FILE *fp;
	fp=fopen("Kullanicilar.txt","a");
 
	if(Durum==1)
	{
     for(int i=0;i<KullaniciSayisi;i++)
	 {
	 
	  if(KKullanici[i].Id==Id)
	{
	KKullanici[i].Durum=0;	
   fprintf(fp,"%d %s %s %s %s %s %s %s %d\n",KKullanici[i].Id,KKullanici[i].Adi,KKullanici[i].Soyad,KKullanici[i].KullaniciAdi,KKullanici[i].Telefon,KKullanici[i].eposta,KKullanici[i].Sifre,KKullanici[i].Ipucu,KKullanici[i].Durum);
	}
	else
	{
  fprintf(fp,"%d %s %s %s %s %s %s %s %d\n",KKullanici[i].Id,KKullanici[i].Adi,KKullanici[i].Soyad,KKullanici[i].KullaniciAdi,KKullanici[i].Telefon,KKullanici[i].eposta,KKullanici[i].Sifre,KKullanici[i].Ipucu,KKullanici[i].Durum);	
	}
	 	
	}
	fclose(fp);

		
		
	}
	
		if(Durum==0)
	{
     for(int i=0;i<KullaniciSayisi;i++)
	 {
	 
	  if(KKullanici[i].Id==Id)
	{
	KKullanici[i].Durum=1;	
   fprintf(fp,"%d %s %s %s %s %s %s %s %d\n",KKullanici[i].Id,KKullanici[i].Adi,KKullanici[i].Soyad,KKullanici[i].KullaniciAdi,KKullanici[i].Telefon,KKullanici[i].eposta,KKullanici[i].Sifre,KKullanici[i].Ipucu,KKullanici[i].Durum);
	}
	else
	{
  fprintf(fp,"%d %s %s %s %s %s %s %s %d\n",KKullanici[i].Id,KKullanici[i].Adi,KKullanici[i].Soyad,KKullanici[i].KullaniciAdi,KKullanici[i].Telefon,KKullanici[i].eposta,KKullanici[i].Sifre,KKullanici[i].Ipucu,KKullanici[i].Durum);	
	}
	 	
	}
	fclose(fp);

		
		
	}
	
	
	
}

void KullaniciIslemleri()
{
git:	
int secim;
char KullaniciAdi[100];	
char Sifre[100];
char Sifre2[100];
char Ipucu[100];
char KullaniciAdi2[100];	
char Ipucu2[100];
system("cls");	
int Secim=0;	
printf("\tSINEMA OTOMASYONUNA HOSGELDINIZ \n");	
TarihGoster();
if(DurumId==-1)
{
printf("\n1-Kullanici Girisi \n2-Sifremi unttum \n3-Bloke kaldirma\n4-Kullanici Olustur\n5-geri don ");	
}
else 
{
printf("\n1-Kullanici Girisi \n2-Sifremi unttum \n3-Bloke kaldirma\n4-Kullanici Olustur\n5-geri don \n99-oturumu kapat");		
}

printf("\n Islem seciniz: ");
scanf("%d",&secim);
if(secim==3)
{
printf("Kullanici adi giriniz: ");
scanf("%s",KullaniciAdi);
printf("Ipucunuzu giriniz: ");
scanf("%s",Ipucu);
int Id=IdGoreKullaniciGetir(KullaniciAdi);	
if(strcmp(KKullanici[Id-1].Ipucu,Ipucu)==0)
{
	BlokeGuncelleme(0,Id);
	printf("Bloke kaldirildi.\nAna Menu geri donuluyor.");
	sleep(3);
  goto git;
}
}
else if(secim==5)
{
AnaIslem();	
}
else if(secim==99)
{
DurumId=-1;
AnaIslem();	
}
	
else if(secim==2)
{
 printf("Kullanici adi giriniz: ");
 scanf("%s",KullaniciAdi2);
 printf("Ipucunuzu giriniz: ");
 scanf("%s",Ipucu2);
  	int Id=IdGoreKullaniciGetir(KullaniciAdi);	
  	printf("%d",Id);
if(strcmp(KKullanici[Id-1].Ipucu,Ipucu2)==0)
{
 printf("Yeni sifrenizi giriniz: ");
 scanf("%s",Sifre);
  printf("Tekrar sifrenizi giriniz: ");
 scanf("%s",Sifre2);
 	remove("Kullanicilar.txt"); 
	FILE *fp;
	fp=fopen("Kullanicilar.txt","a");
	 for(int i=0;i<KullaniciSayisi;i++)
	 {
	 
	  if(KKullanici[i].Id==Id)
	{
		
			printf("x");
   fprintf(fp,"%d %s %s %s %s %s %s %s %d\n",KKullanici[i].Id,KKullanici[i].Adi,KKullanici[i].Soyad,KKullanici[i].KullaniciAdi,KKullanici[i].Telefon,KKullanici[i].eposta,Sifre,KKullanici[i].Ipucu,KKullanici[i].Durum);
	}
	else
	{
  fprintf(fp,"%d %s %s %s %s %s %s %s %d\n",KKullanici[i].Id,KKullanici[i].Adi,KKullanici[i].Soyad,KKullanici[i].KullaniciAdi,KKullanici[i].Telefon,KKullanici[i].eposta,KKullanici[i].Sifre,KKullanici[i].Ipucu,KKullanici[i].Durum);	
	}
	 	
	}
	fclose(fp);
	printf("Sifreniz olusturuldu.Ana menuye donuluyor...");
    sleep(3);
    AnaIslem();	

}

}

if(secim==4)
{
KullaniciOlustur();
printf("Islem basarili sekilde gerceklesmistir.");
sleep(3);
AnaIslem();	
	
	
}

char KullaniciAdi3[100];
char Sifre3[100];
if(secim==1)
{
git5:	
printf("\nKullanici adinizi veya telefon numaranizi giriniz: ");
scanf("%s",KullaniciAdi3);
printf("Sifre giriniz:");
scanf("%s",Sifre3);
int IslemBasarili=KullaniciGirisi(KullaniciAdi3,Sifre3); 
 if(IslemBasarili==99){
printf("Kullanici adi veya sifre yanlis");
goto git5;	

}
else if(IslemBasarili==-1)
{
printf("Kullanici adi veya sifre yanlis");
goto git5;	
}

else
{


	printf("Oturumunuz acildi.. Ana menuye Yonlendirliyorsunuz..");
	int KulId=IdGoreKullaniciGetir(KullaniciAdi3);
	sleep(3);
	DurumId=KulId;
	AnaIslem();	


	




}
}
}





void YorumYap()
{
int Id;
int sec;	
char Yorum[1000];
system("cls");		
printf("\tSINEMA OTOMASYONU\n");	
TarihGoster();
printf("\nYORUMLAR\n");
printf("1-Yorum olustur\n2-Yorumlari gor\n3-Geri don");
printf("\nLutfen islem seciniz: ");
scanf("%d",&sec);
if(sec==1)
{
x:	
if(DurumId==-1)
{
printf("Oturum acmalisiniz Kullanici islemlerine yonlendiriliyorsunuz...");
YorumDurumId=1;
sleep(3);
KullaniciIslemleri();	
}
else
{
  	
}
	
int x=-1;	
for(int i=0;i<FilmSayisi;i++)
{	
printf("Filmin ID : %d\n",FFilmler[i].Id);
printf("Filmin Adi : %s\n",FFilmler[i].Adi);
printf("----------------------------------\n");
}
don:
printf("Filmin Id giriniz: ");
scanf("%d",&Id);
for(int i=0;i<FilmSayisi;i++){
if(Id==FFilmler[i].Id)
{
	x=0;
}	
}
if(x==-1)
goto don;
printf("Yorumunuzu yaziniz: ");
scanf("%s",Yorum);
FILE *fp;
fp=fopen("FilmYorumlari.txt","a");
fprintf(fp,"%d %d %d %s\n",YorumSayisi,Id,DurumId,Yorum);	
fclose(fp);
YorumSayisi++;
YYorum[YorumSayisi].Id=YorumSayisi;
YYorum[YorumSayisi].FilmId=Id;
YYorum[YorumSayisi].KullaniciId=DurumId;
strcpy(YYorum[YorumSayisi].Yorum,Yorum);

printf("Yorumunuz basarili sekilde kaydedildi.");

YorumSayisi=0;
YorumlariCagir();

sleep(3);
AnaIslem();
}	

else if(sec==2)
{
	
system("cls");	
int Secim=0;	
printf("\tYORUMLARI GOR \n");	
TarihGoster();
if(DurumId!=-1)
{
	for(int i=0;i<KullaniciSayisi;i++)
{
	if(KKullanici[i].Id==DurumId)
	{
		printf("\nSayin :%s %s \n",KKullanici[i].Adi,KKullanici[i].Soyad);
	}
}
}


tekrar:
printf("FILM LISTESI");
printf("\n----------------------------\n");
for(int i=0;i<FilmSayisi;i++)
{
printf("(%d) Filmin Adi: %s",FFilmler[i].Id,FFilmler[i].Adi);
printf("\n-----------------------------\n");
	
}	
printf("\nYapmak istediginiz islemi seciniz: ");
scanf("%d",&Secim);

system("cls");
printf("YORUMLAR");
printf("----------------------------\n");
IdGoreFilmGetir(Secim);


	
for(int i=0;i<YorumSayisi;i++)
{
	
	if(YYorum[i].FilmId==Secim)
	{
	printf("\n--------------------------------\n");
	for(int j=0;j<KullaniciSayisi;j++)
    {
	if(KKullanici[j].Id==YYorum[i].KullaniciId)
	{
		printf("\nKisinin Adi Soyadi: :%s %s \n",KKullanici[j].Adi,KKullanici[j].Soyad);
		break;
	}
	

     }
	 
	 printf("Yorumu:\n %s",YYorum[i].Yorum); 
	 		
}
}
y:
printf("\n----------------------------\n");

int sec=0;
printf("\n1-Yorum yaz\n2-Ana menu\n3-Cikis\nLutfen secim yapiniz... ");
scanf("%d",&sec);
switch(sec)
{
case 1: printf("yorum yazma bolumune yonlendiriliyorsunuz."); sleep(3); goto x; break;
case 2: printf("Ana menuye gidiliyor.."); sleep(3); AnaIslem(); break;
case 3: exit(1);
default: goto y; break;
	
}	
}
}


void AnaIslem(){

//Secim yapma isleme 

system("cls");	
int Secim=0;	
printf("\tSINEMA OTOMASYONUNA HOSGELDINIZ \n");	
TarihGoster();
tekrar:
printf("\n1-Rezervasyon Yap \n2-Rezervasyonu iptal et\n3-Filmlerle ilgili yorumlar \n4-Kullanici Islemleri \n5-Cikis");	
printf("\nYapmak istediginiz islemi seciniz: ");
scanf("%d",&Secim);	
switch(Secim){
case 1: Rezervasyon(); break;
case 2: RezervasyonIptal(); break;
case 3: YorumYap(); break;
case 4: KullaniciIslemleri(); break;
case 5: exit(1); break;
default: printf("Gecersiz islem\n"); sleep(3); goto tekrar;	break;
	


}
}




int main()
{
//Burda ilk önce structlarý dolduruldu.	
YorumlariCagir();	
FilmleriCagir();
SalonlariCagir();
SeanslariCagir();
KoltuklariCagir();
SalonSeansCagir();	  	
BiletleriCagir();
KullaniciCagir();
TurleriCagir();
//AnaIslemde ise menulerimiz bulunuyor.
AnaIslem();  
return 0;
}
