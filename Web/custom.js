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
            document.getElementById("demo1").innerHTML = http.responseText;
    });
    http.open("GET", "http://:4000/getdata", true);
    http.setRequestHeader('Content-Type', 'application/json;charset=utf-8;');

    http.send();

}