# ✈️ Flight Management & Passenger Operations System

Bu sistem, uçuş bilgilerini yönetmek ve yolcu operasyonlarını (rezervasyon, iptal, listeleme) terminal üzerinden gerçekleştirmek için tasarlanmış bir **C++** projesidir.

## 🚀 Temel Özellikler

### 1. Uçuş Yönetimi (Top-Level Menu)

**Uçuş Ekleme:** Uçuş numarası ve varış noktası bilgilerini alarak yeni uçuşlar oluşturur.


**Uçuş Silme:** Mevcut uçuşları uçuş numarasıyla sistemden kaldırır.


**Uçuş Listeleme:** Mevcut tüm uçuşların numarasını, hedefini ve boş koltuk sayısını gösterir.



### 2. Yolcu Yönetimi (Second-Level Menu)

**Koltuk Rezervasyonu:** Görsel bir oturma planı üzerinden koltuk seçimi ve yolcu kaydı yapılır.


**Rezervasyon İptali:** Mevcut yolcu bilgilerini doğrulayarak rezervasyonu iptal eder.


**Yolcu Listesi:** Belirli bir uçuşun yolcularını profesyonel tablo formatında listeler.



## 🛠️ Teknik Detaylar

### Sınıf Yapısı (Core Classes)

Sistem üç ana sınıf üzerine inşa edilmiştir:

**FlightManager:** Uçuş listesinin tutulmasından ve uçuş operasyonlarından sorumludur.


**Flight:** Uçuş numarasını, varış noktasını ve koltuk kapasitesini yönetir. Koltuk sayısı çift olmalı ve $maxSeats \leq 80$ kuralına uymalıdır.


**Passenger:** Yolcuların isim, soyisim ve cinsiyet verilerini güvenli bir şekilde tutar.



### Veri Doğrulama (Input Validation)

**Uçuş Numaraları:** Sadece "TK" veya "PG" ile başlamalı ve ardından 1-4 haneli bir sayı gelmelidir.


**İsim Kontrolü:** İsim ve soyisim girişleri sadece alfabetik karakterlerden oluşmalıdır.



### Görsel Formatlama

**Oturma Planı:** Uçak içi düzeni gösteren ızgara yapısında boş koltuklar **'O'**, dolu koltuklar **'X'** ile temsil edilir.


**Yolcu Tablosu:** Koltuk Adı, Yolcu Adı ve Cinsiyet sütunlarından oluşur. 15 karakteri aşan isimler otomatik olarak kesilir ve sonuna nokta eklenir.



## 💻 Kurulum ve Derleme

Projeyi çalıştırmak için:

1. Depoyu klonlayın:
```bash
git clone https://github.com/yagizylldrm/FlightManagementSystem.git

```


2. Dizine gidin:
```bash
cd FlightManagementSystem

```


3. `g++` kullanarak derleyin:
```bash
g++ 202411078_lab_project.cpp -o FlightSystem

```


4. Çalıştırın:
```bash
./FlightSystem

```



---

**Geliştirici:** yagizylldrm

**Proje Tarihi:** 20 Mart 2026

**Ders:** CENG 218 - Data Structures 
