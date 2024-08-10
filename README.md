# My Simple HTTP Server

## Proje Açıklaması

Bu proje, C programlama dili kullanılarak geliştirilmiş bir **basit HTTPS sunucusudur**. Sunucu, SSL/TLS ile güvenli bağlantılar sağlamakta ve istemcilerden gelen HTTP isteklerini işleyerek yanıt vermektedir. Proje, statik dosyalar sunma, kullanıcı geri bildirimlerini işleme ve bir API aracılığıyla JSON formatında veri sağlama gibi temel işlevleri içermektedir.

Projenin amacı, web geliştirme süreçlerini daha iyi anlamak ve C dilinde ağ programlama becerilerini geliştirmektir. Geliştirilen sunucu, kullanıcıların web tarayıcıları aracılığıyla güvenli bir şekilde içerik almasını sağlar ve temel HTTP protokolü ile iletişim kurar. Bu proje, SSL/TLS protokollerini uygulamak için kullanılan OpenSSL kütüphanesi ile donatılmıştır ve C dilindeki uygulamalar için örnek bir temel sunmaktadır.

## Özellikler

- **Güvenli Bağlantı**: OpenSSL kullanılarak kurulan SSL/TLS bağlantıları ile güvenli iletişim sağlar. Bu, veri bütünlüğü ve gizliliği sağlamak için kritik öneme sahiptir.
  
- **Statik Dosya Sunumu**: HTML, CSS ve JavaScript dosyalarını istemcilere sunma yeteneği. Bu özellik, dinamik içerik sunumuna geçiş için bir temel sağlar.
  
- **İstemci Geri Bildirimi**: Kullanıcıdan gelen geri bildirimleri işleyerek yanıt verme. Bu, kullanıcı etkileşimini artırır ve web uygulamalarının kullanıcı ihtiyaçlarına daha iyi yanıt vermesine olanak tanır.
  
- **Basit API**: Kullanıcı bilgilerini JSON formatında sunma. Bu özellik, geliştiricilerin sunucu ile etkileşimde bulunmasını kolaylaştırır.
  
- **Kolay Kurulum**: Basit adımlar ile kurulum ve başlatma süreci. Kullanıcıların projeyi hızlıca çalıştırmasını sağlar.

## Gereksinimler

Projenin çalışabilmesi için aşağıdaki gereksinimlerin karşılanması gerekmektedir:

- **C Derleyicisi**: GCC veya başka bir C derleyicisi.
  
- **OpenSSL Kütüphanesi**: SSL/TLS protokollerini kullanabilmek için gerekli kütüphaneler.
  
- **pthread Kütüphanesi**: Çoklu iş parçacığı desteği için.

## Kurulum Adımları

### 1. Depoyu Klonlayın

Öncelikle projeyi GitHub üzerinden klonlayın:
```bash
git clone https://github.com/kullanici_adiniz/simple-http-server.git
cd simple-http-server
```

### 2. Gerekli Kütüphaneleri Yükleyin

OpenSSL ve diğer gerekli kütüphaneleri yüklemek için terminalde aşağıdaki komutları çalıştırın. Örneğin, Ubuntu için:
```bash
sudo apt-get update
sudo apt-get install libssl-dev
```

### 3. SSL Sertifikası Oluşturma

SSL/TLS için gerekli olan sertifikayı ve özel anahtarı oluşturmak için aşağıdaki komutu kullanın:
```bash
openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout server.key -out server.crt
```
Bu komut sizden bazı bilgiler isteyecektir (ülke, eyalet, organizasyon adı vb.). Bilgileri girdikten sonra, `server.crt` ve `server.key` dosyaları oluşturulacaktır.

### 4. Proje Dosyalarını Derleyin

Proje dizininde aşağıdaki komutu çalıştırarak sunucu uygulamasını derleyin:
```bash
gcc -o https_server https_server.c -lssl -lcrypto -lpthread
```
Bu komut, `https_server` adlı çalıştırılabilir bir dosya oluşturacaktır.

## Kullanım

### 1. Sunucuyu Başlatın

Sunucuyu başlatmak için terminalde şu komutu çalıştırın:
```bash
sudo ./https_server
```
Sunucu, varsayılan olarak 4433 numaralı portta dinlemeye başlayacaktır. Terminalde "Listening on port 4433..." mesajını görmelisiniz.

### 2. Tarayıcıda Test Edin

Tarayıcınızı açın ve `https://localhost:4433` adresine gidin. Güvenlik uyarısı alabilirsiniz; bu, kendi oluşturduğunuz bir sertifika kullanmanızdan kaynaklanıyor. İleri seçeneği ile devam edin ve sunucu ana sayfasını görmelisiniz.

### 3. Geri Bildirim Gönderin

Ana sayfada bulunan geri bildirim formunu doldurarak sunucuya geri bildirim gönderebilirsiniz. Formu doldurduktan sonra gönderdiğiniz bilgiler, sunucu tarafından işlenir ve onay mesajı ile birlikte geri döner.

### 4. Kullanıcıları Listeleme

Kullanıcı bilgilerini JSON formatında görüntülemek için `https://localhost:4433/users` adresine gidin. Bu, sunucu tarafından sağlanan örnek kullanıcı verilerini gösterecektir.

## Proje Yapısı

Aşağıda proje dosyalarının kısa açıklamaları bulunmaktadır:

- `https_server.c`: Sunucu uygulaması, SSL bağlantılarını yönetir, istemci isteklerini işler ve yanıt verir.
- `simple_http_server.h`: Proje genelinde kullanılan fonksiyonların ve değişkenlerin tanımlandığı başlık dosyası.
- `server.crt`: SSL sertifikası dosyası.
- `server.key`: SSL özel anahtarı dosyası.
- `index.html`: Sunucunun ana sayfası için kullanılan HTML dosyası.
- `styles.css`: Ana sayfanın stil dosyası.
- `script.js`: Ana sayfanın JavaScript dosyası.

## Katkıda Bulunma

Bu projeye katkıda bulunmak isterseniz, lütfen aşağıdaki adımları izleyin:

1. Depoyu fork'layın.
2. Yeni bir dal oluşturun (`git checkout -b feature/your-feature`).
3. Değişikliklerinizi yapın ve commit edin (`git commit -m 'Add some feature'`).
4. Dalınızı GitHub'a gönderin (`git push origin feature/your-feature`).
5. Pull request açın.

