# Trên Pi (Nạp HĐH bằng phần mềm Raspberry Pi Imager - Raspberry OS 32 bit (recommend))
- Cài đặt môi trường
+, sudo apt update
+, sudo apt upgrade -y (có thể không cần)
+, sudo apt-get install xrdp
+, sudo apt-get install libevent-dev
+, sudo apt install -y cmake
+, sudo apt install apache2 -y

- Sử dụng
+, apache2: file index.html chứa trong: /var/www/html
+, hostname -I để lấy địa chỉ truy cập apache
a
- Cấu hình apache2
*Thay đổi đường dẫn mặc định (document root)
cd /etc/apache2/sites-available
sudo nano 000-default.conf
Sửa đổi: DocumentRoot /path/to/my/project
sudo service apache2 restart
cd /etc/apache2/
sudo nano apache2.conf
Đổi
 <Directory />
     Options Indexes FollowSymLinks
     AllowOverride All
     Require all denied
 </Directory>
thành
 <Directory />
     Options Indexes FollowSymLinks Includes ExecCGI
     AllowOverride All
     Require all granted
 </Directory>
sudo service apache2 restart