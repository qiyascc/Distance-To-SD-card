// Kitabxananı əlavə edirik.
#include <SPI.h>
#include <SD.h>

// UltraSonic'in pinlərinin bağlı olduğu arduino pinlərini qeyd edək.
#define trigPin 2  // mən ikinciyə bağlamışam.
#define echoPin 3 // mən üçüncüyə bağlamışam.

// UltraSonic üçün dəyərləri təyin edirik.
long duration; // müddət.
int distance; // məsafə.

File myFile; 

// Proseslərin olduğu hissə.
void setup() {
    
// İnformasiya almaq üçün Serial plotter'ı açırıq.
Serial.begin(9600);

// Ultrasonic üçün giriş çıxış pinlərini təyin edirik.
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 

Serial.print("SD kart və ultrasonic sensor yoxlanılır..");

// if else üçün trigPin'i aktivləşdirək.
digitalWrite(trigPin, HIGH);

// Faylı açması/yaratması üçün kod.
myFile = SD.open("qiyascc.txt", FILE_WRITE);
SD.begin(10);

if ((trigPin, LOW) && (!SD.begin(10))) {
    Serial.println("Hal hazırda qarşıda iki problem var.");
    Serial.println("Birincisi: SD kart taxılmayıb vəya modulun bağlantıları doğru deyil.");
    Serial.println("İkincisi: UltraSonic sensor işləmir, bağlantıları yoxlayıb bir də test edin.");      
} else if (!SD.begin(10) && (trigPin, HIGH)) {
        Serial.println("Bir yaxşı və bir pis xəbərim var. Birinci hansını deyim? Nəysə buna özüm qərar verəcəm, ahahah!");
        Serial.println("Pis xəbər: SD kart tapılmadı. SD kart taxılmayıb vəya modulun bağlantıları doğru deyil.");
        Serial.println("Yaxşı xəbər: UltraSonic sensor aktivdir.");
} else if ((trigPin, LOW) && (SD.begin(10))) { 
        Serial.println("Bir yaxşı və bir pis xəbərim var. Birinci hansını deyim? Nəysə buna özüm qərar verəcəm, ahahah!");
        Serial.println("Pis xəbər: UltraSonic sensor işləmir, bağlantıları yoxlayıb bir də test edin.");
        Serial.println("Yaxşı xəbər: SD modulu işləyir.");      
} else if ((SD.begin(10)) && (trigPin, HIGH)) {
        Serial.println("Yoxlanış tamamlandı, UltraSonic sensor və SD kart modulu aktivdir.");
} 

// trigPin'i hələlik söndürək.
digitalWrite(trigPin, LOW);

myFile = SD.open("qiyascc.txt", FILE_WRITE);

// Əgər fayl açılmasa/yaradıla bilməsə xəbərdar olaq.   
if (!myFile) {
        Serial.println("Xəta: fayl açılarkən problem baş verdi, kontrol eləyib təkrar test edin.");
} else {       
        Serial.print("qiyascc.txt faylı yaradıldı.");

//      Açıqlama - fayl daxilində.
        myFile.println("Bu fayl məsafənin ölçümünü qeyd etmək üçün nəzərdə tutulmuşdur.");

//  Məsafəni təyin etmək üçün kodlar.
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        long duration = pulseIn(echoPin, HIGH);
        int distance = duration * 0.034 / 2;
        
//      SD karta məlumatları yazaq.
        Serial.println("Fayl xətasız bir şəkildə açıldı, indi isə məlumatları SD karta yazaq.");
        Serial.println("Məlumatlar SD karta yazılır..");
        myFile.println("Məsafə: ");
        myFile.print(distance);
        myFile.print(" cm.");
        myFile.close();
        Serial.println("Proses uğurla nəticələndi.");
        Serial.println("qiyascc.txt faylı yaradıldı və məsafə qeyd olundu.");
}
while(1);
}

void loop() {
// Bu dəfə buranı işlətmədik.
}
