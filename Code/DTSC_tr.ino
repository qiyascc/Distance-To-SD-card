// Kütüphaneleri ekleyelim. 
#include <SPI.h>
#include <SD.h>

// UltraSonic sensörün bağlı olduğu pinleri yazalım.
#define trigPin 2  // Ben ikiciye bağladım.
#define echoPin 3 // Ben üçüncüye bağladım.

// UltraSonic değerleri belirleyelim.
long duration; // süre.
int distance; // mesafe.

File myFile; 

// Işlemlerin olduğu kısım.
void setup() {
  
Serial.begin(9600);

// UltraSonic sensörün giriş, çıkış pinlerini belirleyelim.
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 

Serial.print("SD kart denetleniyor..");

// trigPin'i çalıştıralım..
digitalWrite(trigPin, HIGH);

// Dosyayı açması/oluşturması için kod.
myFile = SD.open("qiyascc.txt", FILE_WRITE);
SD.begin(10);

if ((trigPin, LOW) && (!SD.begin(10))) {
    Serial.println("Şuan iki sorun var.");
    Serial.println("Birincisi: SD kart ya takılı değil, ya da bağlantılarda sorun var. Kontrol edip tekrar deneyin.");
    Serial.println("İkincisi: UltraSonic sensör çalışmıyor. Bağlantıları kontrol edip tekrar deneyin.");      
} else if (!SD.begin(10) && (trigPin, HIGH)) {
        Serial.println("Bir iyi ve bir kötü haberim var. Önce hangisinden başlayayım? Neyse buna zaten kendim karar vereceğim, ahahaha!");
        Serial.println("Kötü haber: SD kart bulunamadı. SD kart ya takılı değil, ya da bağlantılarda sorun var.");
        Serial.println("Iyi haber: UltraSonic sensör çalışıyor.");
} else if ((trigPin, LOW) && (SD.begin(10))) { 
        Serial.println("Bir iyi ve bir kötü haberim var. Önce hangisinden başlayayım? Neyse buna zaten kendim karar vereceğim, ahahaha!");
        Serial.println("Kötü haber: UltraSonic sensör çalışmıyor.");
        Serial.println("Iyi haber: SD kart bulundu, modulü çalışıyor.");      
} else if ((SD.begin(10)) && (trigPin, HIGH)) {
        Serial.println("Görünüşe göre hiçbir sorun yok, sistem kusursuz bir şekilde çalışıyor.");
} 

// trigPin'i şimdilik kapatalım.
digitalWrite(trigPin, LOW);
 
// Eğer dosya oluşturulmazsa/oluşturulursa uyarı alalım.
if (!myFile) {
        Serial.println("Hata: dosya oluşturulurken sorun oluştu, konteol edip tekrar deneyin.");
} else {       
        Serial.print("qiyascc.txt dosyası oluşturuldu.");

//   Açıklama  - dosya daxilinde.
        myFile.println("Bu dosya ölçülen mesafenin yazılması içindir.");

//  Mesafeyi belirlemek için kodlar.
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        long duration = pulseIn(echoPin, HIGH);
        int distance = duration * 0.034 / 2;
      
  
//      SD karta bilgi aktarımı.
        Serial.println("Dosya açıldı, şimdi de mesafeyi ölçüp yazalım..");
        Serial.println("Bilgiler SD karta yazılıyor...");
        myFile.println("Mesafe: ");
        myFile.print(distance);
        myFile.print(" cm.");
        myFile.close();
        Serial.println("İşlem başarıyla sonlandı..");
        Serial.println("qiyascc.txt dosyası oluşturuldu ve alınan mesafe bilgisi dosyaya kayd edildi.");
}
while(1);
}

void loop() {
// Bu sefer burayı kullanmadık.
}
