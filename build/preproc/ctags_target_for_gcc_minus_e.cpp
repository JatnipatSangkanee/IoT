# 1 "D:\\Project-371\\webserver-mqtt\\webserver-mqtt.ino"
# 2 "D:\\Project-371\\webserver-mqtt\\webserver-mqtt.ino" 2
# 3 "D:\\Project-371\\webserver-mqtt\\webserver-mqtt.ino" 2
# 4 "D:\\Project-371\\webserver-mqtt\\webserver-mqtt.ino" 2
# 5 "D:\\Project-371\\webserver-mqtt\\webserver-mqtt.ino" 2
# 6 "D:\\Project-371\\webserver-mqtt\\webserver-mqtt.ino" 2
# 7 "D:\\Project-371\\webserver-mqtt\\webserver-mqtt.ino" 2

//WiFi want to connect
// #define WIFI_SSID  "CoEIoT"
// #define WIFI_PASS  "iot.coe.psu.ac.th"



// #define WIFI_SSID  "CoEIoT"
// #define WIFI_PASS  "iot.coe.psu.ac.th"


WebServer webServer(80);
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
bool mqttEmailmessage_Recieved = false;



Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

const char *index_html = R"(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Your Page Title</title>
    <style>
        /* Your CSS styles here */
        .button {
            background-color: #00f908; /* Green */
            border: none;
            color: green;
            padding: 15px 32px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
            font-size: 24px;
            cursor: pointer;
            border-radius: 10px; 
        }
    </style>
</head>

<body>
    <div style="background-image: url('https://i.im.ge/2024/03/15/RjWfIh.download-3.jpeg');
    background-size: cover; height:680px; padding-top: 80px; text-align: center;">
        <h1 style="font-size:100px; color:white; margin:10px;">ตู้กดขนมสุดหวานเจี๊ยบ</h1>
        <p style="font-size:30px; color: white;">MangoLight</p>
        <a href="/buy">
            <button class="button" role="button">Buy</button>
        </a>

    </div>
</body>

</html>

)";

const char *buy_html = R"(
<!DOCTYPE html>

    <html>
        <head>
            <meta charset="utf-8">
            <meta name="viewport" content="width=device-width, initial-scale=1">

    <style>
        @import 'https://fonts.googleapis.com/css?family=Kanit Prompt';

        .jumbotron {
            padding: 15px;
            font-family: 'Kanit', sans-serif;
            background: linear-gradient(45deg, #F17C58, #E94584, #24AADB #27DBB1, #FFDC18, #FF3706);
            background-size: 600% 100%;
            background-color: #f0e68c;
            /* ตัวอย่างเป็นสีคากี, คุณสามารถเปลี่ยนเป็นสีที่ต้องการ */

            animation: gradient 5s linear infinite;
            animation-direction: alternate;
            background-repeat: no-repeat;
            /* background-attachment: fixed; */
            background-position: center;
            margin-bottom: 20px;
        }

        @keyframes gradient {
            0% {
                background-position: 0%
            }

            100% {
                background-position: 100%
            }
        }

        .btn-primary {
            background-color: #007bff;
            /* สีพื้นหลัง */
            color: white;
            /* สีข้อความ */
            border: none;
            /* ไม่แสดงเส้นขอบ */
            padding: 10px 20px;
            /* ระยะห่างภายในปุ่ม */
            border-radius: 5px;
            /* ทำให้ขอบปุ่มมน */
            font-size: 16px;
            /* ขนาดข้อความ */
            transition: background-color 0.3s;
            /* เพิ่มการเปลี่ยนแปลงสีเมื่อวางเมาส์ */
            justify-content: center;

        }

        .btn-primary:hover {
            background-color: #0056b3;
            /* สีพื้นหลังเมื่อวางเมาส์ */
        }

        .card {
            margin: 0 auto;
            /* Center the cards */
            box-shadow: 0 4px 8px rgba(1, 78, 11, 0.1);


        }

        .container1 {
            display: grid;
            grid-template-columns: repeat(3, 350px);
            /* 3 columns */
            grid-template-rows: repeat(2, 500px);
            /* 3 rows  */
            /* grid-gap: 50px 30px; */
            /* 50 pixels of space added between rows and 30 pixels added between columns  */
            align-items: center;
            justify-content: center;
        }
        .card img {
            width: 100%;
            height: auto;
            box-shadow: 0 2px 1px rgba(0, 0, 0, 0.1);
            /* เพิ่มเงาให้กับการ์ด */

        }
        .card-img1 {
            width: 80%;
            height: auto;
            box-shadow: 0 2px 1px rgba(0, 0, 0, 0.1);
            /* เพิ่มเงาให้กับการ์ด */

        }

        .center {
            display: block;
            margin-left: auto;
            margin-right: auto;
            width: 50%;
        }

        .card-background {
            background-color: #FFFFFF;
            /* สีพื้นหลังของการ์ด */
            border-radius: 20px;
            /* ทำให้ขอบการ์ดมน */
            box-shadow: 0 20px 28px rgba(0, 0, 0, 0.1);
            /* เพิ่มเงาให้กับการ์ด */

        }

        .card-content-center {
            display: flex;
            justify-content: center;
            align-items: center;
            flex-direction: column;
        }

        .custom-margin {
            margin-bottom: 20px;
            /* เพิ่มระยะห่างด้านล่าง 20px */
            margin-top: 20px;
        }

        .card-title {
            font-size: 20px;
        }
    </style>

    <title>PromptPay QR-Code Javascript Library</title>
    <script src="./promptpay-qr-js-master/promptpay-qr.js"></script>
    <script src="./davidshimjs-qrcodejs-04f46c6/qrcode.min.js"></script>
    <!-- <link href="./app.css" media="all" rel="stylesheet" /> -->
    <script src="https://code.jquery.com/jquery-3.4.1.slim.min.js"
        integrity="sha384-J6qa4849blE2+poT4WnyKhv5vZF5SrPo0iEjwBvKU7imGFAV@wwj1yYfoRSJoZ+n"
        crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js"
        integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9I0Yy5n3zV9zzTtmI3UksdQRVvoxMf"
        crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js"
        integrity="sha384-wfSDF2E50Y2D1uUdj003uMBJnjuUD4Ih7YwaYd1iqfktj0Uod8GCExl30g" crossorigin="anonymous"></script>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css"
        integrity="sha384-Vkoo8x4CGs03+Hhxv8T/Q5PaXtkKtu6ug5T0eNV6g/xh1y9PeLegxhj" crossorigin="anonymous">
</head>

<body>
    <div class="container">
        <!-- Content here -->
        <div class="jumbotron jumbotron-fluid">
            <div class="container">
                <img src="https://i.im.ge/2024/03/17/RPw3pP.b99700d5-0979-4615-ac98-d09f5d416e3d.png"
                    style="width:160px;height:160px;" class="center"></a>
                <center>
                    <h1 class="display-4" style="font-family: 'Anakotmai'">Vending Machine</h1>
                    <p class="lead" style="font-family: 'Itim', sans-serif;font-size: 24px">กรุณาเลือกสินค้าที่ต้องการ
                    </p>
                </center>
            </div>
        </div>



        <div id="qrcode" align="center"></div>
    </div>


    <div class="container1">
        <!-- Card 1 -->
        <div class="col-md-4 custom-margin">
            <div class="card card-background card-img card-content-center" style="width: 18rem;">
                <img src="https://sahathaishoponline.com/wp-content/uploads/2022/11/8851727001021-1.png"
                    class="card-img" alt="ขนมเลย์รสมันฝรั่งแท้" >
                <div class="card-body d-flex flex-column card-content-center">
                    <h5 class="card-title ">ขนมโปเตโต้ 10 บาท</h5>
                    <button  id="payButton1" class="btn btn-primary" >จ่ายเงิน</button>
                </div>
            </div>
        </div>

        <div class="col-md-4 custom-margin">
            <div class="card card card-background card-content-center" style="width: 18rem;">
                <img src="https://st.bigc-cs.com/cdn-cgi/image/format=webp,quality=90/public/media/catalog/product/56/88/8851727003056/8851727003056_1-20230310180054-.jpg"
                    class="card-img1" alt="ขนมคอนเน่" >
                <div class="card-body d-flex flex-column card-content-center">
                    <h5 class="card-title ">ขนมคอนเน่ ราคา 15 บาท</h5>
                    <button id="payButton2" class="btn btn-primary">จ่ายเงิน</button>
                </div>
            </div>
        </div>

        <!-- Card 3 -->
        <div class="col-md-4 custom-margin">
            <div class="card card card-background card-content-center" style="width: 18rem;">
                <img src="https://down-th.img.susercontent.com/file/f96c1530b206432950468cec5c932ea1" class="card-img"
                    alt="ขนมเลย์รสไก่อบน้ำผึ้ง" >
                <div class="card-body d-flex flex-column card-content-center">
                    <h5 class="card-title">ขนมเลย์โรลเลอร์โคสเตอร์ 12 บาท</h5>
                    <button id="payButton3" class="btn btn-primary">จ่ายเงิน</button>
                </div>
            </div>
        </div>
       <div class="col-md-4 custom-margin">

        <div class="card card card-background card-content-center" style="width: 18rem;">
            <!-- <h5 class="card-title"style="font-family: 'Arial', sans-serif;font-size: 24px;text-align: center">ขนมเลย์รสออริจินัล 4 บาท</h5> -->
            <img src="https://www.laemthongfood.co.th/img_product/PACKAGE25141389904771.png"
                class="card-img" alt="ขนมเลย์รสไก่อบน้ำผึ้ง" >
            <div class="card-body d-flex flex-column card-content-center">
                <h5 class="card-title">ขนมอาริงาโตะ 6 บาท</h5>

                <button id="payButton4" class="btn btn-primary ";>จ่ายเงิน</button>
            </div>
        </div>
       </div>
        <div class="col-md-4 custom-margin">
            <div class="card card card-background card-content-center" style="width: 18rem;">
                <!-- <h5 class="card-title"style="font-family: 'Arial', sans-serif;font-size: 24px;text-align: center">ขนมเลย์รสไข่เค็ม 5 บาท</h5> -->
                <img src="https://media.shopat24.com/pdmain/393309-01-potato-chip-lays-v4.jpg"
                    class="card-img" alt="ขนมเลย์รสไก่อบน้ำผึ้ง" >
                <div class="card-body d-flex flex-column card-content-center">
                    <h5 class="card-title">ขนมเลย์คลาสสิค 5 บาท</h5>

                    <button id="payButton5" class="btn btn-primary"  ;>จ่ายเงิน</button>
                </div>
            </div>
        </div>
        <div class="col-sm custom-margin">
            <div class="card card card-background card-content-center" style="width: 18rem;">

                <!-- <h5 class="card-title"style="font-family: 'Arial', sans-serif;font-size: 24px;text-align: center">ขนมเลย์กลิ่นคาราเมล 6 บาท</h5> -->

                <img src="https://st.bigc-cs.com/cdn-cgi/image/format=webp,quality=90/public/media/catalog/product/42/88/8851727002042/8851727002042_1-20230209164400-.jpg"
                    class="card-img" alt="ขนมเลย์รสไก่อบน้ำผึ้ง" >
                <div class="card-body  d-flex flex-column card-content-center">
                    <h5 class="card-title">ขนมปาปริก้า 7 บาท</h5>

                    <button id="payButton6"class="btn btn-primary"  ;>จ่ายเงิน</button>

                </div>
            </div>
        </div>
    </div>
</div>
</body>
<script>
document.addEventListener('DOMContentLoaded', function() {
    // Function to handle QR code generation
    function render_qr(amount) {
        var qr_dom = document.getElementById('qrcode');
        var acc_id = '0950409589'; // Replace with your PromptPay ID
        var txt = PromptPayQR.gen_text(acc_id, amount);
        
        qr_dom.innerHTML = ""; // Clear the QR code container
        if (txt) {
            new QRCode(qr_dom, {
                text: txt,
                width: 128,
                height: 128,
                colorDark : "#000000",
                colorLight : "#ffffff",
                correctLevel : QRCode.CorrectLevel.H
            });
        }
    }

    // Function to scroll to the top of the page
    function scrollToTop() {
        window.scrollTo(0, 0);
    }

    // Add event listeners to buttons
    document.getElementById('payButton1').addEventListener('click', function() {
        render_qr(10); // Pass the amount or other identifier as needed
        scrollToTop();
    });
    document.getElementById('payButton2').addEventListener('click', function() {
        render_qr(14); // Pass the amount or other identifier as needed
        scrollToTop();
    });
    document.getElementById('payButton3').addEventListener('click', function() {
        render_qr(12); // Pass the amount or other identifier as needed
        scrollToTop();
    });
    document.getElementById('payButton4').addEventListener('click', function() {
        render_qr(6); // Pass the amount or other identifier as needed
        scrollToTop();
    });
    document.getElementById('payButton5').addEventListener('click', function() {
        render_qr(5); // Pass the amount or other identifier as needed
        scrollToTop();
    });
    document.getElementById('payButton6').addEventListener('click', function() {
        render_qr(7); // Pass the amount or other identifier as needed
        scrollToTop();
    });

    // Repeat the above block for other buttons as needed, adjusting the ID and parameters
});
    function checkForRedirect() {
        fetch('/check-mqtt')
            .then(response => response.json())
            .then(data => {
                if (data.redirect) {
                    window.location.href = '/thanks'; // Redirect to the game page
                }
            })
            .catch(error => console.error('Error checking for redirect:', error));
    }

    // Poll every 5 seconds
    setInterval(checkForRedirect, 5000);


   var PromptPayQR = {

  // https://gist.github.com/chitchcock/5112270
  // Modified from http://automationwiki.com/index.php?title=CRC-16-CCITT
  checksum: function(s){
    var crcTable = [
      0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5,
      0x60c6, 0x70e7, 0x8108, 0x9129, 0xa14a, 0xb16b,
      0xc18c, 0xd1ad, 0xe1ce, 0xf1ef, 0x1231, 0x0210,
      0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
      0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c,
      0xf3ff, 0xe3de, 0x2462, 0x3443, 0x0420, 0x1401,
      0x64e6, 0x74c7, 0x44a4, 0x5485, 0xa56a, 0xb54b,
      0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
      0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6,
      0x5695, 0x46b4, 0xb75b, 0xa77a, 0x9719, 0x8738,
      0xf7df, 0xe7fe, 0xd79d, 0xc7bc, 0x48c4, 0x58e5,
      0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
      0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969,
      0xa90a, 0xb92b, 0x5af5, 0x4ad4, 0x7ab7, 0x6a96,
      0x1a71, 0x0a50, 0x3a33, 0x2a12, 0xdbfd, 0xcbdc,
      0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
      0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03,
      0x0c60, 0x1c41, 0xedae, 0xfd8f, 0xcdec, 0xddcd,
      0xad2a, 0xbd0b, 0x8d68, 0x9d49, 0x7e97, 0x6eb6,
      0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
      0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a,
      0x9f59, 0x8f78, 0x9188, 0x81a9, 0xb1ca, 0xa1eb,
      0xd10c, 0xc12d, 0xf14e, 0xe16f, 0x1080, 0x00a1,
      0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
      0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c,
      0xe37f, 0xf35e, 0x02b1, 0x1290, 0x22f3, 0x32d2,
      0x4235, 0x5214, 0x6277, 0x7256, 0xb5ea, 0xa5cb,
      0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
      0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447,
      0x5424, 0x4405, 0xa7db, 0xb7fa, 0x8799, 0x97b8,
      0xe75f, 0xf77e, 0xc71d, 0xd73c, 0x26d3, 0x36f2,
      0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
      0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9,
      0xb98a, 0xa9ab, 0x5844, 0x4865, 0x7806, 0x6827,
      0x18c0, 0x08e1, 0x3882, 0x28a3, 0xcb7d, 0xdb5c,
      0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
      0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0,
      0x2ab3, 0x3a92, 0xfd2e, 0xed0f, 0xdd6c, 0xcd4d,
      0xbdaa, 0xad8b, 0x9de8, 0x8dc9, 0x7c26, 0x6c07,
      0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
      0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba,
      0x8fd9, 0x9ff8, 0x6e17, 0x7e36, 0x4e55, 0x5e74,
      0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
    ];
    var crc = 0xFFFF;
    var j, i;
    for (i = 0; i < s.length; i++) {
        c = s.charCodeAt(i);
        if (c > 255) {
            throw new RangeError();
        }
        j = (c ^ (crc >> 8)) & 0xFF;
        crc = crcTable[j] ^ (crc << 8);
    }
    // return %04d
    var chksum = ((crc ^ 0) & 0xFFFF).toString(16);
    return ('0000' + chksum).slice(-4).toUpperCase();
  },

  gen_text: function(acc_id, amount){
    var pp_acc_id = '';
    var pp_amount = '';
    var pp_chksum = '';

    // process acc_id
    if(!acc_id){ // acc_id not found
      return null;
    }
    else if(acc_id.match(/^\d{15}$/)){ // truemoney e-wallet
      pp_acc_id = '0315' + acc_id;
    }
    else if(acc_id.match(/^\d{13}$/)){ // card-id
      pp_acc_id = '0213' + acc_id;
    }
    else if(acc_id.match(/^\d{10}$/)){ // tel-no
      pp_acc_id = '01130066' + acc_id.substr(1);
    }
    else { // invalid acc_id
      return null;
    }
    // process amount
    if(amount){
      amount = amount.toString();
      pp_amount = '54' + ('00' + amount.length).slice(-2) + amount;
    }
    // build pp string
    var field_29 = "0016A000000677010111" + pp_acc_id;
    var pp_str = "000201010211"
                  + "29" + field_29.length + field_29
                  + "5303764"
                  + pp_amount
                  + "5802TH"
                  + "6304";
    // process checksum
    pp_chksum = this.checksum(pp_str);
    pp_str += pp_chksum;
    return pp_str;
  },
}


var QRCode;!function(){function a(a){this.mode=c.MODE_8BIT_BYTE,this.data=a,this.parsedData=[];for(var b=[],d=0,e=this.data.length;e>d;d++){var f=this.data.charCodeAt(d);f>65536?(b[0]=240|(1835008&f)>>>18,b[1]=128|(258048&f)>>>12,b[2]=128|(4032&f)>>>6,b[3]=128|63&f):f>2048?(b[0]=224|(61440&f)>>>12,b[1]=128|(4032&f)>>>6,b[2]=128|63&f):f>128?(b[0]=192|(1984&f)>>>6,b[1]=128|63&f):b[0]=f,this.parsedData=this.parsedData.concat(b)}this.parsedData.length!=this.data.length&&(this.parsedData.unshift(191),this.parsedData.unshift(187),this.parsedData.unshift(239))}function b(a,b){this.typeNumber=a,this.errorCorrectLevel=b,this.modules=null,this.moduleCount=0,this.dataCache=null,this.dataList=[]}function i(a,b){if(void 0==a.length)throw new Error(a.length+'/'+b);for(var c=0;c<a.length&&0==a[c];)c++;this.num=new Array(a.length-c+b);for(var d=0;d<a.length-c;d++)this.num[d]=a[d+c]}function j(a,b){this.totalCount=a,this.dataCount=b}function k(){this.buffer=[],this.length=0}function m(){return'undefined'!=typeof CanvasRenderingContext2D}function n(){var a=!1,b=navigator.userAgent;return/android/i.test(b)&&(a=!0,aMat=b.toString().match(/android ([0-9]\.[0-9])/i),aMat&&aMat[1]&&(a=parseFloat(aMat[1]))),a}function r(a,b){for(var c=1,e=s(a),f=0,g=l.length;g>=f;f++){var h=0;switch(b){case d.L:h=l[f][0];break;case d.M:h=l[f][1];break;case d.Q:h=l[f][2];break;case d.H:h=l[f][3]}if(h>=e)break;c++}if(c>l.length)throw new Error('Too long data');return c}function s(a){var b=encodeURI(a).toString().replace(/\%[0-9a-fA-F]{2}/g,'a');return b.length+(b.length!=a?3:0)}a.prototype={getLength:function(){return this.parsedData.length},write:function(a){for(var b=0,c=this.parsedData.length;c>b;b++)a.put(this.parsedData[b],8)}},b.prototype={addData:function(b){var c=new a(b);this.dataList.push(c),this.dataCache=null},isDark:function(a,b){if(0>a||this.moduleCount<=a||0>b||this.moduleCount<=b)throw new Error(a+','+b);return this.modules[a][b]},getModuleCount:function(){return this.moduleCount},make:function(){this.makeImpl(!1,this.getBestMaskPattern())},makeImpl:function(a,c){this.moduleCount=4*this.typeNumber+17,this.modules=new Array(this.moduleCount);for(var d=0;d<this.moduleCount;d++){this.modules[d]=new Array(this.moduleCount);for(var e=0;e<this.moduleCount;e++)this.modules[d][e]=null}this.setupPositionProbePattern(0,0),this.setupPositionProbePattern(this.moduleCount-7,0),this.setupPositionProbePattern(0,this.moduleCount-7),this.setupPositionAdjustPattern(),this.setupTimingPattern(),this.setupTypeInfo(a,c),this.typeNumber>=7&&this.setupTypeNumber(a),null==this.dataCache&&(this.dataCache=b.createData(this.typeNumber,this.errorCorrectLevel,this.dataList)),this.mapData(this.dataCache,c)},setupPositionProbePattern:function(a,b){for(var c=-1;7>=c;c++)if(!(-1>=a+c||this.moduleCount<=a+c))for(var d=-1;7>=d;d++)-1>=b+d||this.moduleCount<=b+d||(this.modules[a+c][b+d]=c>=0&&6>=c&&(0==d||6==d)||d>=0&&6>=d&&(0==c||6==c)||c>=2&&4>=c&&d>=2&&4>=d?!0:!1)},getBestMaskPattern:function(){for(var a=0,b=0,c=0;8>c;c++){this.makeImpl(!0,c);var d=f.getLostPoint(this);(0==c||a>d)&&(a=d,b=c)}return b},createMovieClip:function(a,b,c){var d=a.createEmptyMovieClip(b,c),e=1;this.make();for(var f=0;f<this.modules.length;f++)for(var g=f*e,h=0;h<this.modules[f].length;h++){var i=h*e,j=this.modules[f][h];j&&(d.beginFill(0,100),d.moveTo(i,g),d.lineTo(i+e,g),d.lineTo(i+e,g+e),d.lineTo(i,g+e),d.endFill())}return d},setupTimingPattern:function(){for(var a=8;a<this.moduleCount-8;a++)null==this.modules[a][6]&&(this.modules[a][6]=0==a%2);for(var b=8;b<this.moduleCount-8;b++)null==this.modules[6][b]&&(this.modules[6][b]=0==b%2)},setupPositionAdjustPattern:function(){for(var a=f.getPatternPosition(this.typeNumber),b=0;b<a.length;b++)for(var c=0;c<a.length;c++){var d=a[b],e=a[c];if(null==this.modules[d][e])for(var g=-2;2>=g;g++)for(var h=-2;2>=h;h++)this.modules[d+g][e+h]=-2==g||2==g||-2==h||2==h||0==g&&0==h?!0:!1}},setupTypeNumber:function(a){for(var b=f.getBCHTypeNumber(this.typeNumber),c=0;18>c;c++){var d=!a&&1==(1&b>>c);this.modules[Math.floor(c/3)][c%3+this.moduleCount-8-3]=d}for(var c=0;18>c;c++){var d=!a&&1==(1&b>>c);this.modules[c%3+this.moduleCount-8-3][Math.floor(c/3)]=d}},setupTypeInfo:function(a,b){for(var c=this.errorCorrectLevel<<3|b,d=f.getBCHTypeInfo(c),e=0;15>e;e++){var g=!a&&1==(1&d>>e);6>e?this.modules[e][8]=g:8>e?this.modules[e+1][8]=g:this.modules[this.moduleCount-15+e][8]=g}for(var e=0;15>e;e++){var g=!a&&1==(1&d>>e);8>e?this.modules[8][this.moduleCount-e-1]=g:9>e?this.modules[8][15-e-1+1]=g:this.modules[8][15-e-1]=g}this.modules[this.moduleCount-8][8]=!a},mapData:function(a,b){for(var c=-1,d=this.moduleCount-1,e=7,g=0,h=this.moduleCount-1;h>0;h-=2)for(6==h&&h--;;){for(var i=0;2>i;i++)if(null==this.modules[d][h-i]){var j=!1;g<a.length&&(j=1==(1&a[g]>>>e));var k=f.getMask(b,d,h-i);k&&(j=!j),this.modules[d][h-i]=j,e--,-1==e&&(g++,e=7)}if(d+=c,0>d||this.moduleCount<=d){d-=c,c=-c;break}}}},b.PAD0=236,b.PAD1=17,b.createData=function(a,c,d){for(var e=j.getRSBlocks(a,c),g=new k,h=0;h<d.length;h++){var i=d[h];g.put(i.mode,4),g.put(i.getLength(),f.getLengthInBits(i.mode,a)),i.write(g)}for(var l=0,h=0;h<e.length;h++)l+=e[h].dataCount;if(g.getLengthInBits()>8*l)throw new Error('code length overflow. ('+g.getLengthInBits()+'>'+8*l+')');for(g.getLengthInBits()+4<=8*l&&g.put(0,4);0!=g.getLengthInBits()%8;)g.putBit(!1);for(;;){if(g.getLengthInBits()>=8*l)break;if(g.put(b.PAD0,8),g.getLengthInBits()>=8*l)break;g.put(b.PAD1,8)}return b.createBytes(g,e)},b.createBytes=function(a,b){for(var c=0,d=0,e=0,g=new Array(b.length),h=new Array(b.length),j=0;j<b.length;j++){var k=b[j].dataCount,l=b[j].totalCount-k;d=Math.max(d,k),e=Math.max(e,l),g[j]=new Array(k);for(var m=0;m<g[j].length;m++)g[j][m]=255&a.buffer[m+c];c+=k;var n=f.getErrorCorrectPolynomial(l),o=new i(g[j],n.getLength()-1),p=o.mod(n);h[j]=new Array(n.getLength()-1);for(var m=0;m<h[j].length;m++){var q=m+p.getLength()-h[j].length;h[j][m]=q>=0?p.get(q):0}}for(var r=0,m=0;m<b.length;m++)r+=b[m].totalCount;for(var s=new Array(r),t=0,m=0;d>m;m++)for(var j=0;j<b.length;j++)m<g[j].length&&(s[t++]=g[j][m]);for(var m=0;e>m;m++)for(var j=0;j<b.length;j++)m<h[j].length&&(s[t++]=h[j][m]);return s};for(var c={MODE_NUMBER:1,MODE_ALPHA_NUM:2,MODE_8BIT_BYTE:4,MODE_KANJI:8},d={L:1,M:0,Q:3,H:2},e={PATTERN000:0,PATTERN001:1,PATTERN010:2,PATTERN011:3,PATTERN100:4,PATTERN101:5,PATTERN110:6,PATTERN111:7},f={PATTERN_POSITION_TABLE:[[],[6,18],[6,22],[6,26],[6,30],[6,34],[6,22,38],[6,24,42],[6,26,46],[6,28,50],[6,30,54],[6,32,58],[6,34,62],[6,26,46,66],[6,26,48,70],[6,26,50,74],[6,30,54,78],[6,30,56,82],[6,30,58,86],[6,34,62,90],[6,28,50,72,94],[6,26,50,74,98],[6,30,54,78,102],[6,28,54,80,106],[6,32,58,84,110],[6,30,58,86,114],[6,34,62,90,118],[6,26,50,74,98,122],[6,30,54,78,102,126],[6,26,52,78,104,130],[6,30,56,82,108,134],[6,34,60,86,112,138],[6,30,58,86,114,142],[6,34,62,90,118,146],[6,30,54,78,102,126,150],[6,24,50,76,102,128,154],[6,28,54,80,106,132,158],[6,32,58,84,110,136,162],[6,26,54,82,110,138,166],[6,30,58,86,114,142,170]],G15:1335,G18:7973,G15_MASK:21522,getBCHTypeInfo:function(a){for(var b=a<<10;f.getBCHDigit(b)-f.getBCHDigit(f.G15)>=0;)b^=f.G15<<f.getBCHDigit(b)-f.getBCHDigit(f.G15);return(a<<10|b)^f.G15_MASK},getBCHTypeNumber:function(a){for(var b=a<<12;f.getBCHDigit(b)-f.getBCHDigit(f.G18)>=0;)b^=f.G18<<f.getBCHDigit(b)-f.getBCHDigit(f.G18);return a<<12|b},getBCHDigit:function(a){for(var b=0;0!=a;)b++,a>>>=1;return b},getPatternPosition:function(a){return f.PATTERN_POSITION_TABLE[a-1]},getMask:function(a,b,c){switch(a){case e.PATTERN000:return 0==(b+c)%2;case e.PATTERN001:return 0==b%2;case e.PATTERN010:return 0==c%3;case e.PATTERN011:return 0==(b+c)%3;case e.PATTERN100:return 0==(Math.floor(b/2)+Math.floor(c/3))%2;case e.PATTERN101:return 0==b*c%2+b*c%3;case e.PATTERN110:return 0==(b*c%2+b*c%3)%2;case e.PATTERN111:return 0==(b*c%3+(b+c)%2)%2;default:throw new Error('bad maskPattern:'+a)}},getErrorCorrectPolynomial:function(a){for(var b=new i([1],0),c=0;a>c;c++)b=b.multiply(new i([1,g.gexp(c)],0));return b},getLengthInBits:function(a,b){if(b>=1&&10>b)switch(a){case c.MODE_NUMBER:return 10;case c.MODE_ALPHA_NUM:return 9;case c.MODE_8BIT_BYTE:return 8;case c.MODE_KANJI:return 8;default:throw new Error('mode:'+a)}else if(27>b)switch(a){case c.MODE_NUMBER:return 12;case c.MODE_ALPHA_NUM:return 11;case c.MODE_8BIT_BYTE:return 16;case c.MODE_KANJI:return 10;default:throw new Error('mode:'+a)}else{if(!(41>b))throw new Error('type:'+b);switch(a){case c.MODE_NUMBER:return 14;case c.MODE_ALPHA_NUM:return 13;case c.MODE_8BIT_BYTE:return 16;case c.MODE_KANJI:return 12;default:throw new Error('mode:'+a)}}},getLostPoint:function(a){for(var b=a.getModuleCount(),c=0,d=0;b>d;d++)for(var e=0;b>e;e++){for(var f=0,g=a.isDark(d,e),h=-1;1>=h;h++)if(!(0>d+h||d+h>=b))for(var i=-1;1>=i;i++)0>e+i||e+i>=b||(0!=h||0!=i)&&g==a.isDark(d+h,e+i)&&f++;f>5&&(c+=3+f-5)}for(var d=0;b-1>d;d++)for(var e=0;b-1>e;e++){var j=0;a.isDark(d,e)&&j++,a.isDark(d+1,e)&&j++,a.isDark(d,e+1)&&j++,a.isDark(d+1,e+1)&&j++,(0==j||4==j)&&(c+=3)}for(var d=0;b>d;d++)for(var e=0;b-6>e;e++)a.isDark(d,e)&&!a.isDark(d,e+1)&&a.isDark(d,e+2)&&a.isDark(d,e+3)&&a.isDark(d,e+4)&&!a.isDark(d,e+5)&&a.isDark(d,e+6)&&(c+=40);for(var e=0;b>e;e++)for(var d=0;b-6>d;d++)a.isDark(d,e)&&!a.isDark(d+1,e)&&a.isDark(d+2,e)&&a.isDark(d+3,e)&&a.isDark(d+4,e)&&!a.isDark(d+5,e)&&a.isDark(d+6,e)&&(c+=40);for(var k=0,e=0;b>e;e++)for(var d=0;b>d;d++)a.isDark(d,e)&&k++;var l=Math.abs(100*k/b/b-50)/5;return c+=10*l}},g={glog:function(a){if(1>a)throw new Error('glog('+a+')');return g.LOG_TABLE[a]},gexp:function(a){for(;0>a;)a+=255;for(;a>=256;)a-=255;return g.EXP_TABLE[a]},EXP_TABLE:new Array(256),LOG_TABLE:new Array(256)},h=0;8>h;h++)g.EXP_TABLE[h]=1<<h;for(var h=8;256>h;h++)g.EXP_TABLE[h]=g.EXP_TABLE[h-4]^g.EXP_TABLE[h-5]^g.EXP_TABLE[h-6]^g.EXP_TABLE[h-8];for(var h=0;255>h;h++)g.LOG_TABLE[g.EXP_TABLE[h]]=h;i.prototype={get:function(a){return this.num[a]},getLength:function(){return this.num.length},multiply:function(a){for(var b=new Array(this.getLength()+a.getLength()-1),c=0;c<this.getLength();c++)for(var d=0;d<a.getLength();d++)b[c+d]^=g.gexp(g.glog(this.get(c))+g.glog(a.get(d)));return new i(b,0)},mod:function(a){if(this.getLength()-a.getLength()<0)return this;for(var b=g.glog(this.get(0))-g.glog(a.get(0)),c=new Array(this.getLength()),d=0;d<this.getLength();d++)c[d]=this.get(d);for(var d=0;d<a.getLength();d++)c[d]^=g.gexp(g.glog(a.get(d))+b);return new i(c,0).mod(a)}},j.RS_BLOCK_TABLE=[[1,26,19],[1,26,16],[1,26,13],[1,26,9],[1,44,34],[1,44,28],[1,44,22],[1,44,16],[1,70,55],[1,70,44],[2,35,17],[2,35,13],[1,100,80],[2,50,32],[2,50,24],[4,25,9],[1,134,108],[2,67,43],[2,33,15,2,34,16],[2,33,11,2,34,12],[2,86,68],[4,43,27],[4,43,19],[4,43,15],[2,98,78],[4,49,31],[2,32,14,4,33,15],[4,39,13,1,40,14],[2,121,97],[2,60,38,2,61,39],[4,40,18,2,41,19],[4,40,14,2,41,15],[2,146,116],[3,58,36,2,59,37],[4,36,16,4,37,17],[4,36,12,4,37,13],[2,86,68,2,87,69],[4,69,43,1,70,44],[6,43,19,2,44,20],[6,43,15,2,44,16],[4,101,81],[1,80,50,4,81,51],[4,50,22,4,51,23],[3,36,12,8,37,13],[2,116,92,2,117,93],[6,58,36,2,59,37],[4,46,20,6,47,21],[7,42,14,4,43,15],[4,133,107],[8,59,37,1,60,38],[8,44,20,4,45,21],[12,33,11,4,34,12],[3,145,115,1,146,116],[4,64,40,5,65,41],[11,36,16,5,37,17],[11,36,12,5,37,13],[5,109,87,1,110,88],[5,65,41,5,66,42],[5,54,24,7,55,25],[11,36,12],[5,122,98,1,123,99],[7,73,45,3,74,46],[15,43,19,2,44,20],[3,45,15,13,46,16],[1,135,107,5,136,108],[10,74,46,1,75,47],[1,50,22,15,51,23],[2,42,14,17,43,15],[5,150,120,1,151,121],[9,69,43,4,70,44],[17,50,22,1,51,23],[2,42,14,19,43,15],[3,141,113,4,142,114],[3,70,44,11,71,45],[17,47,21,4,48,22],[9,39,13,16,40,14],[3,135,107,5,136,108],[3,67,41,13,68,42],[15,54,24,5,55,25],[15,43,15,10,44,16],[4,144,116,4,145,117],[17,68,42],[17,50,22,6,51,23],[19,46,16,6,47,17],[2,139,111,7,140,112],[17,74,46],[7,54,24,16,55,25],[34,37,13],[4,151,121,5,152,122],[4,75,47,14,76,48],[11,54,24,14,55,25],[16,45,15,14,46,16],[6,147,117,4,148,118],[6,73,45,14,74,46],[11,54,24,16,55,25],[30,46,16,2,47,17],[8,132,106,4,133,107],[8,75,47,13,76,48],[7,54,24,22,55,25],[22,45,15,13,46,16],[10,142,114,2,143,115],[19,74,46,4,75,47],[28,50,22,6,51,23],[33,46,16,4,47,17],[8,152,122,4,153,123],[22,73,45,3,74,46],[8,53,23,26,54,24],[12,45,15,28,46,16],[3,147,117,10,148,118],[3,73,45,23,74,46],[4,54,24,31,55,25],[11,45,15,31,46,16],[7,146,116,7,147,117],[21,73,45,7,74,46],[1,53,23,37,54,24],[19,45,15,26,46,16],[5,145,115,10,146,116],[19,75,47,10,76,48],[15,54,24,25,55,25],[23,45,15,25,46,16],[13,145,115,3,146,116],[2,74,46,29,75,47],[42,54,24,1,55,25],[23,45,15,28,46,16],[17,145,115],[10,74,46,23,75,47],[10,54,24,35,55,25],[19,45,15,35,46,16],[17,145,115,1,146,116],[14,74,46,21,75,47],[29,54,24,19,55,25],[11,45,15,46,46,16],[13,145,115,6,146,116],[14,74,46,23,75,47],[44,54,24,7,55,25],[59,46,16,1,47,17],[12,151,121,7,152,122],[12,75,47,26,76,48],[39,54,24,14,55,25],[22,45,15,41,46,16],[6,151,121,14,152,122],[6,75,47,34,76,48],[46,54,24,10,55,25],[2,45,15,64,46,16],[17,152,122,4,153,123],[29,74,46,14,75,47],[49,54,24,10,55,25],[24,45,15,46,46,16],[4,152,122,18,153,123],[13,74,46,32,75,47],[48,54,24,14,55,25],[42,45,15,32,46,16],[20,147,117,4,148,118],[40,75,47,7,76,48],[43,54,24,22,55,25],[10,45,15,67,46,16],[19,148,118,6,149,119],[18,75,47,31,76,48],[34,54,24,34,55,25],[20,45,15,61,46,16]],j.getRSBlocks=function(a,b){var c=j.getRsBlockTable(a,b);if(void 0==c)throw new Error('bad rs block @ typeNumber:'+a+'/errorCorrectLevel:'+b);for(var d=c.length/3,e=[],f=0;d>f;f++)for(var g=c[3*f+0],h=c[3*f+1],i=c[3*f+2],k=0;g>k;k++)e.push(new j(h,i));return e},j.getRsBlockTable=function(a,b){switch(b){case d.L:return j.RS_BLOCK_TABLE[4*(a-1)+0];case d.M:return j.RS_BLOCK_TABLE[4*(a-1)+1];case d.Q:return j.RS_BLOCK_TABLE[4*(a-1)+2];case d.H:return j.RS_BLOCK_TABLE[4*(a-1)+3];default:return void 0}},k.prototype={get:function(a){var b=Math.floor(a/8);return 1==(1&this.buffer[b]>>>7-a%8)},put:function(a,b){for(var c=0;b>c;c++)this.putBit(1==(1&a>>>b-c-1))},getLengthInBits:function(){return this.length},putBit:function(a){var b=Math.floor(this.length/8);this.buffer.length<=b&&this.buffer.push(0),a&&(this.buffer[b]|=128>>>this.length%8),this.length++}};var l=[[17,14,11,7],[32,26,20,14],[53,42,32,24],[78,62,46,34],[106,84,60,44],[134,106,74,58],[154,122,86,64],[192,152,108,84],[230,180,130,98],[271,213,151,119],[321,251,177,137],[367,287,203,155],[425,331,241,177],[458,362,258,194],[520,412,292,220],[586,450,322,250],[644,504,364,280],[718,560,394,310],[792,624,442,338],[858,666,482,382],[929,711,509,403],[1003,779,565,439],[1091,857,611,461],[1171,911,661,511],[1273,997,715,535],[1367,1059,751,593],[1465,1125,805,625],[1528,1190,868,658],[1628,1264,908,698],[1732,1370,982,742],[1840,1452,1030,790],[1952,1538,1112,842],[2068,1628,1168,898],[2188,1722,1228,958],[2303,1809,1283,983],[2431,1911,1351,1051],[2563,1989,1423,1093],[2699,2099,1499,1139],[2809,2213,1579,1219],[2953,2331,1663,1273]],o=function(){var a=function(a,b){this._el=a,this._htOption=b};return a.prototype.draw=function(a){function g(a,b){var c=document.createElementNS('http://www.w3.org/2000/svg',a);for(var d in b)b.hasOwnProperty(d)&&c.setAttribute(d,b[d]);return c}var b=this._htOption,c=this._el,d=a.getModuleCount();Math.floor(b.width/d),Math.floor(b.height/d),this.clear();var h=g('svg',{viewBox:'0 0 '+String(d)+' '+String(d),width:'100%',height:'100%',fill:b.colorLight});h.setAttributeNS('http://www.w3.org/2000/xmlns/','xmlns:xlink','http://www.w3.org/1999/xlink'),c.appendChild(h),h.appendChild(g('rect',{fill:b.colorDark,width:'1',height:'1',id:'template'}));for(var i=0;d>i;i++)for(var j=0;d>j;j++)if(a.isDark(i,j)){var k=g('use',{x:String(i),y:String(j)});k.setAttributeNS('http://www.w3.org/1999/xlink','href','#template'),h.appendChild(k)}},a.prototype.clear=function(){for(;this._el.hasChildNodes();)this._el.removeChild(this._el.lastChild)},a}(),p='svg'===document.documentElement.tagName.toLowerCase(),q=p?o:m()?function(){function a(){this._elImage.src=this._elCanvas.toDataURL('image/png'),this._elImage.style.display='block',this._elCanvas.style.display='none'}function d(a,b){var c=this;if(c._fFail=b,c._fSuccess=a,null===c._bSupportDataURI){var d=document.createElement('img'),e=function(){c._bSupportDataURI=!1,c._fFail&&_fFail.call(c)},f=function(){c._bSupportDataURI=!0,c._fSuccess&&c._fSuccess.call(c)};return d.onabort=e,d.onerror=e,d.onload=f,d.src='data:image/gif;base64,iVBORw0KGgoAAAANSUhEUgAAAAUAAAAFCAYAAACNbyblAAAAHElEQVQI12P4//8/w38GIAXDIBKE0DHxgljNBAAO9TXL0Y4OHwAAAABJRU5ErkJggg==',void 0}c._bSupportDataURI===!0&&c._fSuccess?c._fSuccess.call(c):c._bSupportDataURI===!1&&c._fFail&&c._fFail.call(c)}if(this._android&&this._android<=2.1){var b=1/window.devicePixelRatio,c=CanvasRenderingContext2D.prototype.drawImage;CanvasRenderingContext2D.prototype.drawImage=function(a,d,e,f,g,h,i,j){if('nodeName'in a&&/img/i.test(a.nodeName))for(var l=arguments.length-1;l>=1;l--)arguments[l]=arguments[l]*b;else'undefined'==typeof j&&(arguments[1]*=b,arguments[2]*=b,arguments[3]*=b,arguments[4]*=b);c.apply(this,arguments)}}var e=function(a,b){this._bIsPainted=!1,this._android=n(),this._htOption=b,this._elCanvas=document.createElement('canvas'),this._elCanvas.width=b.width,this._elCanvas.height=b.height,a.appendChild(this._elCanvas),this._el=a,this._oContext=this._elCanvas.getContext('2d'),this._bIsPainted=!1,this._elImage=document.createElement('img'),this._elImage.style.display='none',this._el.appendChild(this._elImage),this._bSupportDataURI=null};return e.prototype.draw=function(a){var b=this._elImage,c=this._oContext,d=this._htOption,e=a.getModuleCount(),f=d.width/e,g=d.height/e,h=Math.round(f),i=Math.round(g);b.style.display='none',this.clear();for(var j=0;e>j;j++)for(var k=0;e>k;k++){var l=a.isDark(j,k),m=k*f,n=j*g;c.strokeStyle=l?d.colorDark:d.colorLight,c.lineWidth=1,c.fillStyle=l?d.colorDark:d.colorLight,c.fillRect(m,n,f,g),c.strokeRect(Math.floor(m)+.5,Math.floor(n)+.5,h,i),c.strokeRect(Math.ceil(m)-.5,Math.ceil(n)-.5,h,i)}this._bIsPainted=!0},e.prototype.makeImage=function(){this._bIsPainted&&d.call(this,a)},e.prototype.isPainted=function(){return this._bIsPainted},e.prototype.clear=function(){this._oContext.clearRect(0,0,this._elCanvas.width,this._elCanvas.height),this._bIsPainted=!1},e.prototype.round=function(a){return a?Math.floor(1e3*a)/1e3:a},e}():function(){var a=function(a,b){this._el=a,this._htOption=b};return a.prototype.draw=function(a){for(var b=this._htOption,c=this._el,d=a.getModuleCount(),e=Math.floor(b.width/d),f=Math.floor(b.height/d),g=['<table style="border:0;border-collapse:collapse;">'],h=0;d>h;h++){g.push('<tr>');for(var i=0;d>i;i++)g.push('<td style="border:0;border-collapse:collapse;padding:0;margin:0;width:"+e+"px;height:"+f+"px;background-color:"+(a.isDark(h,i)?b.colorDark:b.colorLight)+";"></td>');g.push('</tr>')}g.push('</table>'),c.innerHTML=g.join('');var j=c.childNodes[0],k=(b.width-j.offsetWidth)/2,l=(b.height-j.offsetHeight)/2;k>0&&l>0&&(j.style.margin=l+'px '+k+'px')},a.prototype.clear=function(){this._el.innerHTML=''},a}();QRCode=function(a,b){if(this._htOption={width:256,height:256,typeNumber:4,colorDark:'#000000',colorLight:'#ffffff',correctLevel:d.H},'string'==typeof b&&(b={text:b}),b)for(var c in b)this._htOption[c]=b[c];'string'==typeof a&&(a=document.getElementById(a)),this._android=n(),this._el=a,this._oQRCode=null,this._oDrawing=new q(this._el,this._htOption),this._htOption.text&&this.makeCode(this._htOption.text)},QRCode.prototype.makeCode=function(a){this._oQRCode=new b(r(a,this._htOption.correctLevel),this._htOption.correctLevel),this._oQRCode.addData(a),this._oQRCode.make(),this._el.title=a,this._oDrawing.draw(this._oQRCode),this.makeImage()},QRCode.prototype.makeImage=function(){'function'==typeof this._oDrawing.makeImage&&(!this._android||this._android>=3)&&this._oDrawing.makeImage()},QRCode.prototype.clear=function(){this._oDrawing.clear()},QRCode.CorrectLevel=d}();


</script>
</body>
</html>
)";

const char *thanks_html = R"(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Countdown Redirect</title>
<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
<script src="https://code.jquery.com/jquery-3.5.1.slim.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.5.2/dist/umd/popper.min.js"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/js/bootstrap.min.js"></script>
</head>
<body>

<!-- โมดัลป๊อปอัพ -->
<div class="modal" tabindex="-1" role="dialog" id="countdownModal">
  <div class="modal-dialog modal-lg modal-dialog-centered" role="document">
    <div class="modal-content">
      <div class="modal-header justify-content-center">
        <img src="https://i.im.ge/2024/03/17/RPw3pP.b99700d5-0979-4615-ac98-d09f5d416e3d.png"
        style="width:160px;height:160px;display:block;" class="mx-auto">
      </div>
      <div class="text-center">
        <h5 class="modal-title">ขอบคุณที่ซื้อสินค้าครับ</h5>
        <button type="button" class="close" data-dismiss="modal" aria-label="Close">
          <span aria-hidden="true">&times;</span>
        </button>
      </div>
      <div class="modal-body text-center">
        <p id="countdown">Redirecting in 10 seconds.</p>
      </div>
    </div>
  </div>
</div>

<script>
$(document).ready(function() {
    var countdown = 10;

    function updateCountdown() {
        countdown--;
        if(countdown <= 0) {
            document.getElementById("countdown").innerHTML = "ขอบคุณครับ";
            setTimeout(function() {
                window.location.href = "/buy";
            }, 2000);
        } else {
            document.getElementById("countdown").innerHTML = "Redirecting in " + countdown + " seconds.";
            setTimeout(updateCountdown, 500);
        }
    }

    $('#countdownModal').modal('show');
    setTimeout(updateCountdown, 1000);
});

window.addEventListener('load', function() {
    // Call the reset-payment-status endpoint to reset the payment status
    fetch('/reset-payment-status')
        .then(response => {
            if (response.ok) {
                console.log('Payment status reset successfully');
            } else {
                console.error('Failed to reset payment status');
            }
        })
        .catch(error => console.error('Error resetting payment status:', error));
});
</script>

</body>
</html>
)";

// void Servo_Machine(){
//   String MachineTopic = "esp32/servo";
//   String MachineStateStr = "unlock";
//   mqttClient.publish(MachineTopic.c_str(), MachineStateStr.c_str());
// }


void setupWiFi() {
  Serial.println();
  Serial.println("Connecting to " + String("Redmi Note 11") + " ...");

  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin("Redmi Note 11", "29311111111");

  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
      Serial.println("Failed to connect to the Wi-Fi network, restarting...");
      delay(2000);
      ESP.restart();
  }

  Serial.println("Wi-Fi connected, browse to http://" + WiFi.localIP().toString());
}
void resetPaymentStatus() {
    mqttEmailmessage_Recieved = false;
}
void setupWebServer() {
  webServer.on("/", HTTP_GET, []() {
      webServer.send(200, "text/html", index_html);
  });

  webServer.on("/buy", HTTP_GET, []() {
      String page = buy_html;
      webServer.send(200, "text/html", page);
  });

  webServer.on("/getPaymentData", HTTP_GET, []() {
        StaticJsonDocument<200> doc;
        doc["mqtt"] = mqttEmailmessage_Recieved;

        String json;
        serializeJson(doc, json);

        webServer.send(200, "application/json", json);
    });
  webServer.on("/setPaymentData", HTTP_POST, []() {
      mqttEmailmessage_Recieved = webServer.arg("mqtt") == "true" ? true : false;
      webServer.send(200, "text/plain", "Success");
  });


    webServer.on("/reset-payment-status", HTTP_GET, []() {
        mqttEmailmessage_Recieved = false;
        webServer.send(200, "text/plain", "Payment status reset successfully");
    });

  webServer.on("/thanks", HTTP_GET, []() {
      webServer.send(200, "text/html", thanks_html);
  });

  webServer.on("/check-mqtt", HTTP_GET, []() {
  StaticJsonDocument<200> doc;
  doc["redirect"] = mqttEmailmessage_Recieved;
  String json;
  serializeJson(doc, json);
  webServer.send(200, "application/json", json);
});

  webServer.begin();
}

// void mqttCallback(const char *topic, byte *message, unsigned int length) {
//   String messageStr = String((char*)message).substring(0, length);

//   Serial.print("Message arrived [");
//   Serial.print(topic);
//   Serial.print("]: ");
//   Serial.println(messageStr);

//   // Check for specific message and topic
//     if (String(topic) == "iot1" && messageStr == "paymentsed") {
//         mqttEmailmessage_Recieved = true;
//     }
// }
void controlServo(int servoChannel, int delayTime) {
  Serial.print("Controlling servo on channel: ");
  Serial.print(servoChannel);
  Serial.print(" with delay: ");
  Serial.print(delayTime);
  Serial.println(" milliseconds.");

  // สมมติว่าเราคำนวณค่า PWM จากองศา (0-180) และส่งค่าไปยังเซอร์โว
  int pulse = map(servoChannel, 0, 6, 180, 360);
  pwm.setPWM(servoChannel, 0, pulse);


  // บันทึกเวลาเริ่มต้น
  unsigned long startTime = millis();
  Serial.print("Starting delay at: ");
  Serial.println(startTime);

  delay(delayTime); // ใช้เวลา delay

  // บันทึกเวลาหลังจาก delay
  unsigned long endTime = millis();
  Serial.print("Ending delay at: ");
  Serial.println(endTime);

  // คำนวณและแสดงเวลาที่ใช้จริง
  Serial.print("Actual delay time: ");
  Serial.print(endTime - startTime);
  Serial.println(" milliseconds.");

  // หยุดเซอร์โว
  pwm.setPWM(servoChannel, 0, 0);
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Callback triggered!");

  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Payload: ");

  String payloadStr = "";
  for (int i = 0; i < length; i++) {
    payloadStr += (char)payload[i];
  }
  Serial.println(payloadStr);
  if (String(topic) == "iot1" && payloadStr == "paymentsed") {
    mqttEmailmessage_Recieved = true;
  }

  // ทำการควบคุม Servo 2, 4, 6 ตามค่าที่รับมาจาก MQTT
  if (payloadStr == "10BATH") {
    Serial.println("Selected Servo 2 for 1 BATH");
    controlServo(1,4000);
  } else if (payloadStr == "14BATH") {
    controlServo(2,5500);
  } else if (payloadStr == "12BATH") {
    controlServo(3,5000);
  } else if (payloadStr == "6BATH") {
    controlServo(4,6500);
  } else if (payloadStr == "5BATH") {
    controlServo(5,10000);
  } else if (payloadStr == "7BATH") {
    controlServo(0,3500);
  }
  Serial.println("Callback executed."); // Add this line for debugging

}

void setupMqttClient() {
    mqttClient.setServer("192.168.204.159", 1883);
    mqttClient.setCallback(mqttCallback);

    Serial.println("Connecting to MQTT broker " + String("192.168.204.159") + ":" + String(1883));

    while(!mqttClient.connected()) {
        if (mqttClient.connect("ESP32-web")) {
            // device/<MAC_ADDRESS>/led/<LED_NUMBER>/command
            // String EmailTopic = "iot1/email";
            // String CoinTopic = "iot1/coin";
            mqttClient.subscribe("iot1");

            Serial.println("Connected to MQTT broker");
            // Serial.println("Subscribing to topic: " + EmailTopic);
            // Serial.println("Subscribing to topic: " + CoinTopic);

            // mqttClient.subscribe(EmailTopic.c_str());
        }
        else {
            Serial.println("Failed to connect to MQTT broker, retrying in 5 seconds...");
            delay(5000);
        }
    }
}

void setup() {
    Serial.begin(115200);
    setupWiFi();
    setupWebServer();
    setupMqttClient();
    ElegantOTA.begin(&webServer);

    String esp32IPAddress = WiFi.localIP().toString();
    //print IP in Serial Moniter
    Serial.println("\nWiFi connected, IP: " + esp32IPAddress);
    mqttClient.setCallback(mqttCallback);

  // ติดต่อ PCA9685
    pwm.begin();
    pwm.setPWMFreq(60);
}


void loop() {
    webServer.handleClient();
    mqttClient.loop();
    ElegantOTA.loop();
}
