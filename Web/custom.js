function tableCreate(number, obj_name, obj_MSV, obj_DD)
{
    document.open();
    // create body
    document.write(`
        <table style="width:100%"; border=1;>
        <tr>
        <th>STT</th>
        <th>Họ và tên</th>
        <th>MSV</th>
        <th>Điểm danh</th>
        </tr>
    `);

    for (var i = 0; i < number; i++)
    {
        document.write(`
            <tr>
                <td>${i+1}</td>
                <td>${obj_name[i]}</td>
                <td>${obj_MSV[i]}</td>
                <td>${obj_DD[i]}</td>
            </tr>
        `);
    }
    document.write("</table>");
    document.close();
}
function getData()
{
    var http = new XMLHttpRequest();
    http.addEventListener("load", function (){
        if (this.readyState == 4 && this.status == 200)
        {
            document.getElementById("demo1").innerHTML = http.responseText;
            console.log(http.responseText);
            let value = JSON.parse(http.responseText);
            console.log(value.ass.a);

            let aName = {0:"Học sinh 1", 1:"Học sinh 2", 2:"Học sinh 3", 3:"Học sinh 4", 4:"Học sinh 5", 5:"Học sinh 6",
                         6:"Học sinh 7", 7:"Học sinh 8", 8:"Học sinh 9"};
            let aMSV  = {0:123456789, 1:1234567119, 2:12345678921, 3:123456789, 4:1234567119, 5:12345678921,
                         6:123456789, 7:1234567119, 8:12345678921};
            let aDD = {0:"Chưa điểm danh", 1:"Đã điểm danh", 2:"Đã điểm danh"};
            tableCreate(9, aName, aMSV, aDD);
        }
        else
        {
            document.getElementById("demo1").innerHTML = "ERROR";
        }
    });
    http.open("GET", "http://192.168.0.200:4000/getdata", true);
    http.setRequestHeader('Content-Type', 'application/json;charset=utf-8;');
    http.send();
}