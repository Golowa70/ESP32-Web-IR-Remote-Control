const base_url = 'http://192.168.1.183';

const ipList = [];
const btnDevice1 = document.getElementById("btnDevice1");
const btnDevice2 = document.getElementById("btnDevice2");
const btnDevice3 = document.getElementById("btnDevice3");

if (ipList.length > 0) {
    printList(ipList);
}

btnDevice1.onclick = () => {    // off to test
    fetch(`${base_url}/relay/off`,{ mode: 'no-cors'})
        .then((response) => response.json())
        .then((json) => console.log(json))
        .catch(error => {
            console.log(`Error status:${error.message}`)
        });
}

btnDevice2.onclick = () => {    // on to test
    fetch(`${base_url}/relay/on`,{ mode: 'no-cors'})
        .then((response) => response.json())
        .then((json) => console.log(json))
        .catch(error => {
            console.log(`Error status:${error.message}`)
        });
}

// btnDevice1.onclick = () => {
//     fetch(`${base_url}/relay/on`, {
//         method: 'Post',
//         body: JSON.stringify("select_device_1"),
//         headers: {
//             'Content-Type': 'application/json'
//         }
//     })
//         .then(response => response.json())
//         .then(data => console.log(data))
//         .catch(e => console.log(e));
// }


function printList(ipList) {
    const list = document.createElement('ol')
    for (let i = 0; i < ipList.length; i++) {
        const text = document.createTextNode(ipList[i]);
        const li = document.createElement('li');
        li.appendChild(text);
        list.appendChild(li);
    }
    if (result.firstElementChild) {
        result.replaceChild(list, result.firstElementChild);
    } else {
        result.appendChild(list);
    }

}

function findIP(list, ip) {
    for (let i = 0; i < list.length; i++) {
        if (list[i] === ip) {
            return i;
        }
    }
    return -1;
}

