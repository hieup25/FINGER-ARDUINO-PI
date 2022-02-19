function tableCreate(number, obj_name, obj_MSV, obj_DD, time_)
{
    // Tạo bảng
    var table = document.getElementById('table');
    table.style.width = '100%';
    table.setAttribute('border', 1);
    // Tạo cột 1
    var r1 = document.createElement('tr');
    var th1 = document.createElement('th');
    th1.style.width = '3%';
    th1.innerText = "STT";
    var th2 = document.createElement('th');
    th2.style.width = '20%';
    th2.innerText = "Họ và Tên";
    var th3 = document.createElement('th');
    th3.style.width = '20%';
    th3.innerText = "MSV";
    var th4 = document.createElement('th');
    th4.innerText = "Điểm Danh";
    th4.style.width = '20%';
    
    var th5 = document.createElement('th');
    th5.innerText = "Thời gian";

    r1.appendChild(th1);
    r1.appendChild(th2);
    r1.appendChild(th3);
    r1.appendChild(th4);
    r1.appendChild(th5);
    table.appendChild(r1);
    //
    let time = new Date();
    for (var i = 0; i < number; i++)
    {
        let rows = document.createElement('tr');
        let td1 = document.createElement('td');
        td1.style.textAlign = 'center';
        td1.innerText = i + 1;

        let td2 = document.createElement('td');
        td2.innerText = obj_name[i];

        let td3 = document.createElement('td');
        td3.innerText = obj_MSV[i];

        let td4 = document.createElement('td');
        if (obj_DD[i] == 1)
            td4.innerText = "Đã điểm danh";
        else
            td4.innerText = "Chưa điểm danh";

        let get = time_[i] + " ngày " + time.getDate() + "/" + (time.getMonth() + 1);
        // let get = time.getHours() + ":" + time.getMinutes() + " ngày " + time.getDate() + "/" + (time.getMonth() + 1);
        let td5 = document.createElement('td');
        if (obj_DD[i] == 1)
            td5.innerText = get;
        else
            td5.innerText = "Chưa có dữ liệu";
        rows.appendChild(td1);
        rows.appendChild(td2);
        rows.appendChild(td3);
        rows.appendChild(td4);
        rows.appendChild(td5);
        table.appendChild(rows);
    }
}
function getData()
{
    var http = new XMLHttpRequest();
    http.addEventListener("load", function (){
        if (this.readyState == 4 && this.status == 200)
        {
            //document.getElementById("status").innerText = http.responseText;
            // console.log(http.responseText);
            let value = JSON.parse(http.responseText);
            let aName = {0:"Học sinh 1", 1:"Học sinh 2", 2:"Học sinh 3", 3:"Học sinh 4", 4:"Học sinh 5", 5:"Học sinh 6",
                         6:"Học sinh 7", 7:"Học sinh 8", 8:"Học sinh 9"};
            let aMSV  = {0:123456789, 1:1234567119, 2:12345678921, 3:123456789, 4:1234567119, 5:12345678921,
                         6:123456789, 7:1234567119, 8:12345678921};
            let aDD = {};
            let time = {};
            let size_ = Object.keys(value.data).length;
            console.log(size_);
            for (var i = 0; i < size_; i++)
            {
                const n = Object.values(value.data[i]); // 1 đã điẻm danh, 0 chưa điểm danh
                aDD[i] = n[0];
                time[i] = n[1];
            }
            tableCreate(9, aName, aMSV, aDD, time);
        }
        else
        {
            document.getElementById("status").innerText = "Server Not Found";
        }
    });
    http.open("GET", "http://192.168.0.200:4000/getdata", true);
    http.setRequestHeader('Content-Type', 'application/json;charset=utf-8;');
    http.send();
}