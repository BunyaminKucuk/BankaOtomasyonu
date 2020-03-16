#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>//sleep komutu icin gerekli kütüphane
#include<locale.h>//turkce karakterler icin

struct musteriBilgileri
{
   char *adres;
   char *mail;
   char *telefon;
};
struct kimlik
{
    char *ad;
    char *soyad;
    char *hesapNo;
    char *musteriNo;
    int bakiye;
    struct musteriBilgileri bilgi;
};
void musteriEkle();
void hesapActirma();
double altihane();
void para_transfer();
int alici(int);
int para_islem(int);
void sil();
void musteriEkleT();
void hesapActirmaT();
double altihane();
void para_transferT();
int aliciT(int);
int para_islemT(int);
void silT();

typedef struct kimlik kayit;
kayit oku;
int hesap_no=0;
int miktar=0,bakiye=0;
int sorgu=0;
int  tut_bakiye=0,son_bakiye=0;
char gsorgu[106];

FILE *dosya,*dosya1;
int main()
{
    setlocale(LC_ALL, "Turkish");
    int secim,secim1;
    char tercih;
    bas:
        printf("\n\n\t\t\t\t***BANKA OTOMASYONU***\n\n\t\t\t\t\n");
        printf("\n\t******MENU******\n");
        printf("\t1)BIREYSEL HESAP\n\t2)TICARI HESAP\n\t3)CIKIS\nSeciminiz:"); scanf("%d",&secim);
        system("CLS");
        switch(secim)
        {//menu secme
        case 1:
            {//bireysel hesap
                 printf("\n\n\t\t\t\t***BANKA OTOMASYONU***\n\n\t\t\t\t\n");
                 printf("\n\t******MENU******\n");
                 printf("1)Yeni Musteri Ekleme\n2)Hesap Olusturma\n3)Para Cekme\n4)Para Yatirma\n5)Hesaba Havale\n6)Banka Gelir Gider Raporu\n7)Hesap Ozeti\n8)Hesap Kapama\n\nSeciminiz:");
                 scanf("%d",&secim1);
                 switch(secim1)
                 {//alt menu secimi
                 case 1:
                    {//musteri ekleme
                        musteriEkle();
                        printf("\n\n\t\t\tBILGILER KAYDEDILIYOR...\t\t\t\n\n");
                        Sleep(1500);
                        system("CLS");
                        printf("\n\n\tMENUYE YONLENDIRILIYORSUNUZ\t\n\n");
                        Sleep(1500);
                        system("CLS");
                        goto bas;
                        break;
                    }//musteri ekleme
                 case 2:
                    {//hesap olusturma
                      hesapActirma();
                      printf("\n\n\tHesabiniz acilmistir\t\n\n");
                      Sleep(1500);
                      system("CLS");
                      printf("\n\n\tMENUYE YONLENDIRILIYORSUNUZ\t\n\n");
                      Sleep(1500);
                      system("CLS");
                      goto bas;
                      break;
                    }//hesap olsturma
                 case 3:
                    {//para cekme
                        typedef struct kimlik kayit;
                        kayit oku;
                      hesapnogir:
			          printf("Lutfen kullanicinin hesap numarasini giriniz : ");
                      scanf("%d",&sorgu);
                     tut_bakiye=para_islem(sorgu);
					while(tut_bakiye==0)
					{
						system("CLS");
						goto hesapnogir;
						printf("\n");
					}
					printf("\nCekmek istediginiz miktari giriniz : ");
					scanf("%d",&miktar);
					while(miktar>tut_bakiye)
					{
						printf("Bakiyeniz yeterli degildir.\nMevcut bakiyeniz %d.\nLutfen tekrar giriniz : ",tut_bakiye);
						scanf("%d",&miktar);
					}
					while(miktar<=0)
					{
						printf("Yanlis tutar girdiniz.\nMevcut bakiyeniz %d.\nLutfen tekrar giriniz : ",tut_bakiye);
						scanf("%d",&miktar);
					}
					while(miktar>750)
                    {
                        printf("Gunluk para cekme limitini gectiniz.\nLimitiniz 750 TL\nLutfen miktari tekrar giriniz :");
                        scanf("%d",&miktar);
                    }
					dosya=fopen("bireyselkayit.txt","r");
					dosya1=fopen("kayit2.txt","w");
					oku.hesapNo=(char*)malloc(sizeof(char)*100);
					oku.ad=(char*)malloc(sizeof(char)*100);
					oku.soyad=(char*)malloc(sizeof(char)*100);
					itoa(sorgu,gsorgu,10);
					while(!feof(dosya))
					{
						fscanf(dosya,"%s %s %s %d",oku.hesapNo,oku.ad,oku.soyad,&oku.bakiye);
						if(strcmp(oku.hesapNo,gsorgu)==0)
						{
							oku.bakiye=tut_bakiye-miktar;
							son_bakiye=oku.bakiye;
							fprintf(dosya1,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
						}
						if(strcmp(oku.hesapNo,gsorgu)==0)
						{
							continue;
						}
						if(feof(dosya))
						{
							break;
						}
						fprintf(dosya1,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
					}
					printf("\nPara cekme islemi basarili!\nKalan bakiye : %d ",son_bakiye);;
					fclose(dosya);
					fclose(dosya1);
					remove("bireyselkayit.txt");
					rename("kayit2.txt","bireyselkayit.txt");
					goto bas;
					break;
                    }//para cekme
                 case 4:
                    {//para yatirma
                        hesapnogi:
                        printf("Para cekilecek hesap numarasini giriniz:");
                        scanf("%d",&sorgu);
                        tut_bakiye=para_islem(sorgu);
                        while(tut_bakiye==0)
                        {
                            system("CLS");
                            goto hesapnogi;
                            printf("\n");
                        }
                        printf("Yatirmak istediginiz miktari giriniz:");
                        scanf("%d",&miktar);
                    dosya=fopen("bireyselkayit.txt","r");
					dosya1=fopen("kayit2.txt","w");
					oku.hesapNo=(char*)malloc(sizeof(char)*100);
					oku.ad=(char*)malloc(sizeof(char)*100);
					oku.soyad=(char*)malloc(sizeof(char)*100);
					itoa(sorgu,gsorgu,10);
					while(!feof(dosya))
					{
						fscanf(dosya,"%s %s %s %d",oku.hesapNo,oku.ad,oku.soyad,&oku.bakiye);
						if(strcmp(oku.hesapNo,gsorgu)==0)
						{
							oku.bakiye=tut_bakiye+miktar;
							son_bakiye=oku.bakiye;
							fprintf(dosya1,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
						}
						if(strcmp(oku.hesapNo,gsorgu)==0)
						{
							continue;
						}
						if(feof(dosya))
						{
							break;
						}
						fprintf(dosya1,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
					}
					printf("Para yatiriliyor\n");
					Sleep(1500);
					printf("Para yatirma isleminiz  basarili olmustur.\nYeni bakiye:%d",son_bakiye);
					Sleep(1500);
					fclose(dosya);
					fclose(dosya1);
					remove("bireyselkayit.txt");
					rename("kayit2.txt","bireyselkayit.txt");
                    system("CLS");
					goto bas;
					break;
                    }//para yatirma
                 case 5:
                    {//hesaba havale
			           para_transfer();
			           goto bas;
			           break;
                    }//hesaba havale
                 case 6:
                    {//banka gelir-gider raporu

                    }//banka gelir-gider raporu
                 case 7:
                    {//hesap ozeti

                    }//hesap ozeti
                 case 8:
                    {//hesap slme
                        sil();
                        printf("Hesap kapaniyor\n");
                        Sleep(1500);
                        printf("\nHesap silindi.Menuye yönlendiriliyorsunuz...");
                        Sleep(1500);
                        goto bas;
                        break;
                    }//hesap silme
                 }//alt menu secimi
                 break;
            }//bireysel hesap
             case 2:
                {//ticari hesap
                          printf("\n\n\t\t\t\t***BANKA OTOMASYONU***\n\n\t\t\t\t\n");
                 printf("\n\t******MENU******\n");
                 printf("1)Yeni Musteri Ekleme\n2)Hesap Olusturma\n3)Para Cekme\n4)Para Yatirma\n5)Hesaba Havale\n6)Banka Gelir Gider Raporu\n7)Hesap Ozeti\n8)Hesap Kapama\n\nSeciminiz:");
                 scanf("%d",&secim1);
                 switch(secim1)
                 {//alt menu secimi
                 case 1:
                    {//musteri ekleme
                        musteriEkleT();
                        printf("\n\n\t\t\tBILGILER KAYDEDILIYOR...\t\t\t\n\n");
                        Sleep(1500);
                        system("CLS");
                        printf("\n\n\tMENUYE YONLENDIRILIYORSUNUZ\t\n\n");
                        Sleep(1500);
                        system("CLS");
                        goto bas;
                        break;
                    }//musteri ekleme
                 case 2:
                    {//hesap olusturma
                      hesapActirmaT();
                      printf("\n\n\tHesabiniz acilmistir\t\n\n");
                      Sleep(1500);
                      system("CLS");
                      printf("\n\n\tMENUYE YONLENDIRILIYORSUNUZ\t\n\n");
                      Sleep(1500);
                      system("CLS");
                      goto bas;
                      break;
                    }//hesap olsturma
                 case 3:
                    {//para cekme
                      hesapnogir1:
			          printf("Lutfen kullanicinin hesap numarasini giriniz : ");
                      scanf("%d",&sorgu);
                     tut_bakiye=para_islemT(sorgu);
					while(tut_bakiye==0)
					{
						system("CLS");
						goto hesapnogir1;
						printf("\n");
					}
					printf("\nCekmek istediginiz miktari giriniz : ");
					scanf("%d",&miktar);
					while(miktar>tut_bakiye)
					{
						printf("Bakiyeniz yeterli degildir.\nMevcut bakiyeniz %d.\nLutfen tekrar giriniz : ",tut_bakiye);
						scanf("%d",&miktar);
					}
					while(miktar<=0)
					{
						printf("Yanlis tutar girdiniz.\nMevcut bakiyeniz %d.\nLutfen tekrar giriniz : ",tut_bakiye);
						scanf("%d",&miktar);
					}
					while(miktar>1500)
                    {
                        printf("Gunluk para cekme limitini gectiniz.\nLimitiniz 1500 TL\nLutfen miktari tekrar giriniz :");
                        scanf("%d",&miktar);
                    }
					dosya=fopen("ticarikayit.txt","r");
					dosya1=fopen("kayit2.txt","w");
					oku.hesapNo=(char*)malloc(sizeof(char)*100);
					oku.ad=(char*)malloc(sizeof(char)*100);
					oku.soyad=(char*)malloc(sizeof(char)*100);
					itoa(sorgu,gsorgu,10);
					while(!feof(dosya))
					{
						fscanf(dosya,"%s %s %s %d",oku.hesapNo,oku.ad,oku.soyad,&oku.bakiye);
						if(strcmp(oku.hesapNo,gsorgu)==0)
						{
							oku.bakiye=tut_bakiye-miktar;
							son_bakiye=oku.bakiye;
							fprintf(dosya1,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
						}
						if(strcmp(oku.hesapNo,gsorgu)==0)
						{
							continue;
						}
						if(feof(dosya))
						{
							break;
						}
						fprintf(dosya1,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
					}
					printf("\nPara cekme islemi basarili!\nKalan bakiye : %d ",son_bakiye);;
					fclose(dosya);
					fclose(dosya1);
					remove("ticarikayit.txt");
					rename("kayit2.txt","ticarikayit.txt");
					goto bas;
					break;
                    }//para cekme
                 case 4:
                    {//para yatirma
                        hesapnogi1:
                        printf("Para cekilecek hesap numarasini giriniz:");
                        scanf("%d",&sorgu);
                        tut_bakiye=para_islemT(sorgu);
                        while(tut_bakiye==0)
                        {
                            system("CLS");
                            goto hesapnogi1;
                            printf("\n");
                        }
                        printf("Yatirmak istediginiz miktari giriniz:");
                        scanf("%d",&miktar);
                    dosya=fopen("ticarikayit.txt","r");
					dosya1=fopen("kayit2.txt","w");
					oku.hesapNo=(char*)malloc(sizeof(char)*100);
					oku.ad=(char*)malloc(sizeof(char)*100);
					oku.soyad=(char*)malloc(sizeof(char)*100);
					itoa(sorgu,gsorgu,10);
					while(!feof(dosya))
					{
						fscanf(dosya,"%s %s %s %d",oku.hesapNo,oku.ad,oku.soyad,&oku.bakiye);
						if(strcmp(oku.hesapNo,gsorgu)==0)
						{
							oku.bakiye=tut_bakiye+miktar;
							son_bakiye=oku.bakiye;
							fprintf(dosya1,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
						}
						if(strcmp(oku.hesapNo,gsorgu)==0)
						{
							continue;
						}
						if(feof(dosya))
						{
							break;
						}
						fprintf(dosya1,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
					}
					printf("Para yatiriliyor\n");
					Sleep(1500);
					printf("Para yatirma isleminiz  basarili olmustur.\nYeni bakiye:%d",son_bakiye);
					Sleep(1500);
					fclose(dosya);
					fclose(dosya1);
					remove("ticarikayit.txt");
					rename("kayit2.txt","ticarikayit.txt");
                    system("CLS");
					goto bas;
					break;
                    }//para yatirma
                 case 5:
                    {//hesaba havale
			           para_transferT();
			           goto bas;
			           break;
                    }//hesaba havale
                 case 6:
                    {//banka gelir-gider raporu

                    }//banka gelir-gider raporu
                 case 7:
                    {//hesap ozeti

                    }//hesap ozeti
                 case 8:
                    {//hesap slme
                        silT();
                        printf("Hesap kapaniyor\n");
                        Sleep(1500);
                        printf("\nHesap silindi.Menuye yönlendiriliyorsunuz...");
                        Sleep(1500);
                        goto bas;
                        break;
                    }//hesap silme
                 }//alt menu secimi
                 break;
                }//ticari hesap
            case 3:
                {//cikis
                    printf("\nCikis yapmak mi istiyorsunuz"); scanf("%s",&tercih);
                    if(tercih=='e' ||tercih=='E')
                    {
                        printf("Cikis yapiliyor");
                        Sleep(1500);
                        printf("\n\n\n\t\t<<<<<TEKRAR BEKLERIZ>>>>>\n\n\n\t\t");
                        exit(1);
                    }

                    else if(tercih=='h'||tercih=='H')
                        goto bas;
                    else
                        printf("Yanlis secim yaptiniz");
                        printf("Menuye yonlendiriliyorsunuz");
                        Sleep(1500);
                        goto bas;
                    break;
                }//cikis
        }//menu secme
}//main
void musteriEkle()
{
    double musteri_no;
    srand(time(NULL));
    printf("\n\nKAYIT EKRANI\n------------\nKisini\n------------\nAdi   :");
    oku.ad=(char*)malloc(sizeof(char)*100);//malloc komutu ada gore hafýzada tutulan alani degitiriyor
    scanf("%s",oku.ad);
    oku.soyad=(char*)malloc(sizeof(char)*100);
    printf("\nSoyadi  :");
    scanf("%s",oku.soyad);
    oku.bilgi.adres=(char*)malloc(sizeof(char)*100);
    printf("\nAdres(Bitisik yaziniz lutfen)  :");
    scanf("%s",oku.bilgi.adres);
    oku.bilgi.mail=(char*)malloc(sizeof(char)*100);
    printf("\nE-posta  :");
    scanf("%s",oku.bilgi.mail);
    oku.bilgi.telefon=(char*)malloc(sizeof(char)*100);
    printf("\nTelefon  :");
    scanf("%s",oku.bilgi.telefon);
    oku.musteriNo=(char*)malloc(sizeof(char)*100);
    musteri_no=altihane();
    itoa(musteri_no,oku.musteriNo,10);//int degiskenini stringe çevirip Hexadesimal1(6),Binar(2) veya 10luk tabanina göre yaziyor
    printf("\nMusteri No:%s(LUTFEN NOT EDINIZ..!)",oku.musteriNo);
    dosya=fopen("bireyselmusterikayit.txt","a");
    fprintf(dosya,"%s %s %s %s %s %s \n",oku.musteriNo,oku.ad,oku.soyad,oku.bilgi.adres,oku.bilgi.telefon,oku.bilgi.mail);
    fclose(dosya);
    system("CLS");
}
void hesapActirma()
{
    double Hesap_No;
    srand(time(NULL));
    oku.ad=(char*)malloc(sizeof(char)*100);
    printf("\n\nKAYIT EKRANI\n------------\nKisinin\n------------\nAdi  :");
    scanf("%s",oku.ad);
    oku.soyad=(char*)malloc(sizeof(char)*100);
    printf("\nSoyadi :");
    scanf("%s",oku.soyad);
    oku.hesapNo=(char*)malloc(sizeof(char)*100);
    Hesap_No=altihane();
    itoa(Hesap_No,oku.hesapNo,10);
    printf("\nYeni hesap no:%s(Lutfen not ediniz)",oku.hesapNo);
    printf("\nLutfen ilk bakiyenizi giriniz:");
    scanf("%d",&oku.bakiye);
    dosya=fopen("bireyselkayit.txt","a");
    fprintf(dosya,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
    fclose(dosya);
    system("CLS");
}
int alici(int miktar)
{
     char secim_onay;
     printf("Gonderilecek hesap icin\n-----------------------\nLutfen kullanicinin hesap numarasini giriniz :");
     hesapnogir:
     scanf("%d",&sorgu);
     tut_bakiye=para_islem(sorgu);
     printf("Ek olarak %.2f TL islem ucreti kesilecektir\n",miktar*0.02);
     printf("%d hesap numarali hesaba, %d TL gonderilecek.\nOnayliyor musunuz?[E/H]",sorgu,miktar);
     secimnoktasi:
     scanf("%s",&secim_onay);
     if(secim_onay=='E' || secim_onay=='e')
     {
         dosya=fopen("bireyselkayit.txt","r");
         dosya1=fopen("kayit2.txt","w");
         oku.hesapNo=(char*)malloc(sizeof(char)*100);
         oku.ad=(char*)malloc(sizeof(char)*100);
         oku.soyad=(char*)malloc(sizeof(char)*100);
         itoa(sorgu,gsorgu,10);
         while(!feof(dosya))
         {
             fscanf(dosya,"%s %s %s %d",oku.hesapNo,oku.ad,oku.soyad,&oku.bakiye);
             if(strcmp(oku.hesapNo,gsorgu)==0)
             {
                 oku.bakiye=tut_bakiye+miktar;
                 son_bakiye=oku.bakiye;
                 fprintf(dosya1,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
             }
             if(strcmp(oku.hesapNo,gsorgu)==0)
             {
                 continue;
             }
             if(feof(dosya))
             {
                 break;
             }
             fprintf(dosya1,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
         }
         printf("\n\n\tIslemler gerceklesiyor...\t\n\n");
         printf("Havale islemi basarali\nYeni bakiye :%d TL",son_bakiye);
         fclose(dosya);
         fclose(dosya1);
         remove("bireyselkayit.txt");
         rename("kayit2.txt","bireyselkayit.txt");
         return son_bakiye;
     }
     else if(secim_onay=='H' || secim_onay=='h')
     {
         printf("\nIslemden vazgeciliyor...");
         Sleep(1500);
         printf("\nIsleminiz iptal edilmistir.Ana menuye yonlendiriliyorsunuz");
         Sleep(1500);
         system("CLS");
         son_bakiye=-1;
         return son_bakiye;
     }
     else
     {
         printf("\nYanlis secim yaptiniz.Lutfen[E/H] harflerinden birine basiniz.");
         goto secimnoktasi;
     }
}
void para_transfer()
{
    int tut=0;
    printf("Gonderen hesap icin\n-----------------------\nLutfen  hesap numaranizi giriniz :");
    hesapnogir:
    scanf("%d",&sorgu);
    if((tut_bakiye=para_islem(sorgu))==(0))
    {
        printf("\nBu hesap numarsi yanlis.Lufen tekrardan giriniz.\n");
        goto hesapnogir;
    }
    else
    {
        printf("\nGondermek istedginiz miktari giriniz :");
        scanf("%d",&miktar);
        while(miktar>tut_bakiye)
        {
            printf("Bakiyeniz yeterli degildir.\nMevcut bakiyeniz %d.Lutfen mikari tekar giriniz :",tut_bakiye);
            scanf("%d",&miktar);
        }
        while(miktar<=0)
        {
            printf("\nBu hesapta yeterli bakiye yok.\nLutfen tekrardan hesap numarasi giriniz :");
            goto hesapnogir;
        }
        if(alici(miktar)!=0)//eger islemden vazgeçilirse alici fonksiyonundan -1 degeri gelecek ve bu isleme devam etmeyecek
        {
            dosya=fopen("bireyselkayit.txt","r");
            dosya1=fopen("kayit2.txt","w");
            oku.hesapNo=(char*)malloc(sizeof(char)*100);
            oku.ad=(char*)malloc(sizeof(char)*100);
            oku.soyad=(char*)malloc(sizeof(char)*100);
            itoa(sorgu,gsorgu,10);
            while(!feof(dosya))
            {
                fscanf(dosya,"%s %s %s %d",oku.hesapNo,oku.ad,oku.soyad,&oku.bakiye);
                if(strcmp(oku.hesapNo,gsorgu)==0)
                {
                    oku.bakiye=(tut_bakiye-(miktar+(miktar*0.02)));
                    tut=oku.bakiye;
                    fprintf(dosya1,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
                }
                if(strcmp(oku.hesapNo,gsorgu)==0)
                {
                    continue;
                }
                if(feof(dosya))
                {
                    break;
                }
                fprintf(dosya1,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
            }
            fclose(dosya);
            fclose(dosya1);
            remove("bireyselkayit.txt");
            rename("kayit2.txt","bireyselkayit.txt");
        }
    }
}

int para_islem(int sorgu)
{
	int sakla, say;
	FILE *fp=fopen("bireyselkayit.txt","r");
	oku.hesapNo=(char*)malloc(sizeof(char)*100);
	oku.ad=(char*)malloc(sizeof(char)*100);
	oku.soyad=(char*)malloc(sizeof(char)*100);
	itoa(sorgu,gsorgu,10);
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %s %d",oku.hesapNo,oku.ad,oku.soyad,&oku.bakiye);
		if(strcmp(oku.hesapNo,gsorgu)==0)
		{
			printf("Hesap no : %s\n\nKisinin\n------------\n Adi    : %s\n Soyadi : %s\n Bakiye : %d TL\n------------\n\n\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
			++say;
			sakla=oku.bakiye;
		}
	}
	if(say==0)
	{
		printf("\nHesap bulunamadi.");
		sakla=0;
	}
	fclose(fp);
	return sakla;
}
void musteriEkleT()
{
    double musteri_no;
    srand(time(NULL));
    printf("\n\nKAYIT EKRANI\n------------\nKisini\n------------\nAdi   :");
    oku.ad=(char*)malloc(sizeof(char)*100);//malloc komutu ada gore hafýzada tutulan alani degitiriyor
    scanf("%s",oku.ad);
    oku.soyad=(char*)malloc(sizeof(char)*100);
    printf("\nSoyadi  :");
    scanf("%s",oku.soyad);
    oku.bilgi.adres=(char*)malloc(sizeof(char)*100);
    printf("\nAdres(Bitisik yaziniz lutfen)  :");
    scanf("%s",oku.bilgi.adres);
    oku.bilgi.mail=(char*)malloc(sizeof(char)*100);
    printf("\nE-posta  :");
    scanf("%s",oku.bilgi.mail);
    oku.bilgi.telefon=(char*)malloc(sizeof(char)*100);
    printf("\nTelefon  :");
    scanf("%s",oku.bilgi.telefon);
    oku.musteriNo=(char*)malloc(sizeof(char)*100);
    musteri_no=altihane();
    itoa(musteri_no,oku.musteriNo,10);//int degiskenini stringe çevirip Hexadesimal1(6),Binar(2) veya 10luk tabanina göre yaziyor
    printf("\nMusteri No:%s(LUTFEN NOT EDINIZ..!)",oku.musteriNo);
    dosya=fopen("ticarimusterikayit.txt","a");
    fprintf(dosya,"%s %s %s %s %s %s \n",oku.musteriNo,oku.ad,oku.soyad,oku.bilgi.adres,oku.bilgi.telefon,oku.bilgi.mail);
    fclose(dosya);
    system("CLS");
}
void hesapActirmaT()
{
    double Hesap_No;
    srand(time(NULL));
    oku.ad=(char*)malloc(sizeof(char)*100);
    printf("\n\nKAYIT EKRANI\n------------\nKisinin\n------------\nAdi  :");
    scanf("%s",oku.ad);
    oku.soyad=(char*)malloc(sizeof(char)*100);
    printf("\nSoyadi :");
    scanf("%s",oku.soyad);
    oku.hesapNo=(char*)malloc(sizeof(char)*100);
    Hesap_No=altihane();
    itoa(Hesap_No,oku.hesapNo,10);
    printf("\nYeni hesap no:%s(Lutfen not ediniz)",oku.hesapNo);
    printf("\nLutfen ilk bakiyenizi giriniz:");
    scanf("%d",&oku.bakiye);
    dosya=fopen("ticarikayit.txt","a");
    fprintf(dosya,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
    fclose(dosya);
    system("CLS");
}
int aliciT(int miktar)
{
     char secim_onay;
     printf("Gonderilecek hesap icin\n-----------------------\nLutfen kullanicinin hesap numarasini giriniz :");
     hesapnogir:
     scanf("%d",&sorgu);
     tut_bakiye=para_islemT(sorgu);
    // printf("Ek olarak %.2f TL islem ucreti kesilecektir\n",miktar*0.02);
     printf("%d hesap numarali hesaba, %d TL gonderilecek.\nOnayliyor musunuz?[E/H]",sorgu,miktar);
     secimnoktasi:
     scanf("%s",&secim_onay);
     if(secim_onay=='E' || secim_onay=='e')
     {
         dosya=fopen("ticarikayit.txt","r");
         dosya1=fopen("kayit2.txt","w");
         oku.hesapNo=(char*)malloc(sizeof(char)*100);
         oku.ad=(char*)malloc(sizeof(char)*100);
         oku.soyad=(char*)malloc(sizeof(char)*100);
         itoa(sorgu,gsorgu,10);
         while(!feof(dosya))
         {
             fscanf(dosya,"%s %s %s %d",oku.hesapNo,oku.ad,oku.soyad,&oku.bakiye);
             if(strcmp(oku.hesapNo,gsorgu)==0)
             {
                 oku.bakiye=tut_bakiye+miktar;
                 son_bakiye=oku.bakiye;
                 fprintf(dosya1,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
             }
             if(strcmp(oku.hesapNo,gsorgu)==0)
             {
                 continue;
             }
             if(feof(dosya))
             {
                 break;
             }
             fprintf(dosya1,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
         }
         printf("\n\n\tIslemler gerceklesiyor...\t\n\n");
         printf("Havale islemi basarali\nYeni bakiye :%d TL",son_bakiye);
         fclose(dosya);
         fclose(dosya1);
         remove("ticarikayit.txt");
         rename("kayit2.txt","ticarikayit.txt");
         return son_bakiye;
     }
     else if(secim_onay=='H' || secim_onay=='h')
     {
         printf("\nIslemden vazgeciliyor...");
         Sleep(1500);
         printf("\nIsleminiz iptal edilmistir.Ana menuye yonlendiriliyorsunuz");
         Sleep(1500);
         system("CLS");
         son_bakiye=-1;
         return son_bakiye;
     }
     else
     {
         printf("\nYanlis secim yaptiniz.Lutfen[E/H] harflerinden birine basiniz.");
         goto secimnoktasi;
     }
}
void para_transferT()
{
    int tut=0;
    printf("Gonderen hesap icin\n-----------------------\nLutfen  hesap numaranizi giriniz :");
    hesapnogir:
    scanf("%d",&sorgu);
    if((tut_bakiye=para_islemT(sorgu))==(0))
    {
        printf("\nBu hesap numarsi yanlis.Lufen tekrardan giriniz.\n");
        goto hesapnogir;
    }
    else
    {
        printf("\nGondermek istedginiz miktari giriniz :");
        scanf("%d",&miktar);
        while(miktar>tut_bakiye)
        {
            printf("Bakiyeniz yeterli degildir.\nMevcut bakiyeniz %d.Lutfen mikari tekar giriniz :",tut_bakiye);
            scanf("%d",&miktar);
        }
        while(miktar<=0)
        {
            printf("\nBu hesapta yeterli bakiye yok.\nLutfen tekrardan hesap numarasi giriniz :");
            goto hesapnogir;
        }
        if(aliciT(miktar)!=0)//eger islemden vazgeçilirse alici fonksiyonundan -1 degeri gelecek ve bu isleme devam etmeyecek
        {
            dosya=fopen("ticarikayit.txt","r");
            dosya1=fopen("kayit2.txt","w");
            oku.hesapNo=(char*)malloc(sizeof(char)*100);
            oku.ad=(char*)malloc(sizeof(char)*100);
            oku.soyad=(char*)malloc(sizeof(char)*100);
            itoa(sorgu,gsorgu,10);
            while(!feof(dosya))
            {
                fscanf(dosya,"%s %s %s %d",oku.hesapNo,oku.ad,oku.soyad,&oku.bakiye);
                if(strcmp(oku.hesapNo,gsorgu)==0)
                {
                    oku.bakiye=tut_bakiye-miktar;
                    tut=oku.bakiye;
                    fprintf(dosya1,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
                }
                if(strcmp(oku.hesapNo,gsorgu)==0)
                {
                    continue;
                }
                if(feof(dosya))
                {
                    break;
                }
                fprintf(dosya1,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
            }
            fclose(dosya);
            fclose(dosya1);
            remove("ticarikayit.txt");
            rename("kayit2.txt","ticarikayit.txt");
        }
    }
}

int para_islemT(int sorgu)
{
	int sakla, say;
	FILE *fp=fopen("ticarikayit.txt","r");
	oku.hesapNo=(char*)malloc(sizeof(char)*100);
	oku.ad=(char*)malloc(sizeof(char)*100);
	oku.soyad=(char*)malloc(sizeof(char)*100);
	itoa(sorgu,gsorgu,10);
	while(!feof(fp))
	{
		fscanf(fp,"%s %s %s %d",oku.hesapNo,oku.ad,oku.soyad,&oku.bakiye);
		if(strcmp(oku.hesapNo,gsorgu)==0)
		{
			printf("Hesap no : %s\n\nKisinin\n------------\n Adi    : %s\n Soyadi : %s\n Bakiye : %d TL\n------------\n\n\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
			++say;
			sakla=oku.bakiye;
		}
	}
	if(say==0)
	{
		printf("\nHesap bulunamadi.");
		sakla=0;
	}
	fclose(fp);
	return sakla;
}
void sil()
{
    int say;
	char onay_silme[06];
	FILE *rfp;
	rfp=fopen("bireyselkayit.txt","r");
	oku.hesapNo=(char*)malloc(sizeof(char)*100);
	oku.ad=(char*)malloc(sizeof(char)*100);
	oku.soyad=(char*)malloc(sizeof(char)*100);
	printf("\n\nAranacak kisinin hesap numarasini giriniz:");
	scanf("%d",&sorgu);
	time_t basla,bit;
 	time (&basla);
	itoa(sorgu,gsorgu,10);
	while(!feof(rfp))
	{

		fscanf(rfp,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,&oku.bakiye);
		if(strcmp(oku.hesapNo,gsorgu)==0)
		{
			printf("\nSONUC\n------------\n\nHesap no : %s\n\nKisinin\n------------\n Adi    : %s\n Soyadi : %s\n Bakiye : %d TL\n------------\n\n\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
			say++;
		}
	}
		if(say==0)
		{
			printf("Hesap bulunamadi.Ana menuye donuluyor");
			fclose(rfp);
			goto sona;
		}
	fclose(rfp);

	printf("\nYukarida bulunan %s nolu hesap silinecek.Onayliyor musunuz?[E/H] : ",gsorgu);
	secimnoktasi:
	scanf("%s",onay_silme);
	if(strcmp(onay_silme,"e")==0||strcmp(onay_silme,"E")==0)
	{
		FILE *ofp=fopen("bireyselkayit.txt","r");
		FILE *nfp=fopen("gecici.txt","w");
		while(!feof(ofp))
		{
			fscanf(ofp,"%s %s %s %d",oku.hesapNo,oku.ad,oku.soyad,&oku.bakiye);
			if(strcmp(oku.hesapNo,gsorgu)==0)
			{
				continue;
			}
			if(feof(ofp))
			{

				break;
			}
			fprintf(nfp,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
		}
		printf("\n%s nolu hesap silindi.Ana menuye donuluyor",gsorgu);
		time (&bit);
		printf ("\nIsleminiz %.2lf saniye surdu.\n", difftime (bit,basla));
		fclose(nfp);
		fclose(ofp);
		remove("bireyselkayit.txt");
		rename("gecici.txt","bireyselkayit.txt");

	}
	else if(strcmp(onay_silme,"h")==0||strcmp(onay_silme,"H")==0)
	{
		printf("\nVazgectiniz.Ana menuye donuluyor");
		goto sona;
	}
	else
	{
	printf("\nYanlis harfe bastiniz.Lutfen [E/H] harflerinden birine basiniz.\nSeciminiz : ");
	goto secimnoktasi;
	}

		sona://goto deðiþkeni
		system("CLS");
}
void silT()
{
	int say;
    char onay_silme[06];
	FILE *rfp;
	rfp=fopen("ticarikayit.txt","r");
	oku.hesapNo=(char*)malloc(sizeof(char)*100);
	oku.ad=(char*)malloc(sizeof(char)*100);
	oku.soyad=(char*)malloc(sizeof(char)*100);
	printf("\n\nAranacak kisinin hesap numarasini giriniz:");
	scanf("%d",&sorgu);
	time_t basla,bit;
 	time (&basla);
	itoa(sorgu,gsorgu,10);
	while(!feof(rfp))
	{

		fscanf(rfp,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,&oku.bakiye);
		if(strcmp(oku.hesapNo,gsorgu)==0)
		{
			printf("\nSONUC\n------------\n\nHesap no : %s\n\nKisinin\n------------\n Adi    : %s\n Soyadi : %s\n Bakiye : %d TL\n------------\n\n\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
			say++;
		}
	}
		if(say==0)
		{
			printf("Hesap bulunamadi.Ana menuye donuluyor");
			fclose(rfp);
			goto sona;
		}
	fclose(rfp);

	printf("\nYukarida bulunan %s nolu hesap silinecek.Onayliyor musunuz?[E/H] : ",gsorgu);
	secimnoktasi:
	scanf("%s",onay_silme);
	if(strcmp(onay_silme,"e")==0||strcmp(onay_silme,"E")==0)
	{
		FILE *ofp=fopen("ticarikayit.txt","r");
		FILE *nfp=fopen("gecici.txt","w");
		while(!feof(ofp))
		{
			fscanf(ofp,"%s %s %s %d",oku.hesapNo,oku.ad,oku.soyad,&oku.bakiye);
			if(strcmp(oku.hesapNo,gsorgu)==0)
			{
				continue;
			}
			if(feof(ofp))
			{

				break;
			}
			fprintf(nfp,"%s %s %s %d\n",oku.hesapNo,oku.ad,oku.soyad,oku.bakiye);
		}
		printf("\n%s nolu hesap silindi.Ana menuye donuluyor",gsorgu);
		time (&bit);
		printf ("\nIsleminiz %.2lf saniye surdu.\n", difftime (bit,basla));
		fclose(nfp);
		fclose(ofp);
		remove("ticarikayit.txt");
		rename("gecici.txt","ticarikayit.txt");

	}
	else if(strcmp(onay_silme,"h")==0||strcmp(onay_silme,"H")==0)
	{
		printf("\nVazgectiniz.Ana menuye donuluyor");
		goto sona;
	}
	else
	{
	printf("\nYanlis harfe bastiniz.Lutfen [E/H] harflerinden birine basiniz.\nSeciminiz : ");
	goto secimnoktasi;
	}

		sona://goto deðiþkeni
		system("CLS");
}
double altihane()
{
    double alti_h;
	srand(time(NULL));
	alti_h=1+rand()%9;
	if(alti_h<2)
	{
		alti_h+=100000+rand()%32767+rand()%32767+rand()%32767;
	}
	else if(alti_h<3)
	{
		alti_h+=200000+rand()%32767+rand()%32767+rand()%32767;
	}
	else if(alti_h<4)
	{
		alti_h+=300000+rand()%32767+rand()%32767+rand()%32767;
	}
	else if(alti_h<5)
	{
		alti_h+=400000+rand()%32767+rand()%32767+rand()%32767;
	}
	else if(alti_h<6)
	{
		alti_h+=500000+rand()%32767+rand()%32767+rand()%32767;
	}
	else if(alti_h<7)
	{
		alti_h+=600000+rand()%32767+rand()%32767+rand()%32767;
	}
	else if(alti_h<8)
	{
		alti_h+=700000+rand()%32767+rand()%32767+rand()%32767;
	}
	else if(alti_h<9)
	{
		alti_h+=800000+rand()%32767+rand()%32767+rand()%32767;
	}
	else
	{
		alti_h+=900000+rand()%32767+rand()%32767+rand()%32767;
	}
	return alti_h;
}
