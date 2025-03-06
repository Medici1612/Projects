
function updateTableEntry(tag, index) {
    const entry = document.getElementsByTagName('tr')[index + 1];

    const obj = {};
    for (let i = 0; i < entry.childElementCount - 2; i++) {
        const cell = entry.childNodes.item(i);
        console.log(cell);

        const key = cell.getAttribute('data-key');
        const value = cell.children[0].value;

        obj[key] = value;
    }

    const data = JSON.parse(localStorage.getItem(tag) ?? '[]') || [];
    data[index] = obj;
    localStorage.setItem(tag, JSON.stringify(data));

    window.location.reload();
}

function deleteTableEntry(tag, index) {
    const data = JSON.parse(localStorage.getItem(tag) ?? '[]') || [];

    data.splice(index, 1);
    console.log(tag, index);
    console.log(data);

    localStorage.setItem(tag, JSON.stringify(data));

    window.location.reload();
}

function main() {
    const tabela = document.querySelector('#tabela');

    const tag = tabela.getAttribute('data-tag');
    const headers = document.createElement('thead');
    const dados = document.createElement('tbody');

    tabela.appendChild(headers);
    tabela.appendChild(dados);

    const isAdmin = JSON.parse(localStorage.getItem('sessao')).Email == 'admin';

    let objetos = JSON.parse(localStorage.getItem(tag)) || [];

    const header = document.createElement('tr');
    for (const coluna of Object.keys(objetos[0])) {
        const valorHeader = document.createElement('th');
        valorHeader.innerText = coluna;
        header.appendChild(valorHeader);
    }
    if (isAdmin) {
        const colunaUpdate = document.createElement('th');
        colunaUpdate.innerText = 'Update'
        header.appendChild(colunaUpdate);

        const colunaDelete = document.createElement('th');
        colunaDelete.innerText = 'Delete'
        header.appendChild(colunaDelete);
    }
    headers.appendChild(header);

    let index = 0;
    for (const objeto of objetos) {
        let linha = document.createElement('tr');
        for (const coluna of Object.keys(objeto)) {
            const data = document.createElement('td');
            if (!isAdmin) {
                data.innerText = objeto[coluna];
            }
            else {
                data.setAttribute('data-key', coluna);
                const input = document.createElement('input');
                input.value = objeto[coluna];
                data.appendChild(input);
            }
            linha.appendChild(data);
        }
        if (isAdmin) {
            const celulaUpdate = document.createElement('td');
            const botaoUpdate = document.createElement('button');
            botaoUpdate.classList.add('button');
            botaoUpdate.innerText = 'Update';
            botaoUpdate.addEventListener('click', updateTableEntry.bind(null, tag, index));
            celulaUpdate.appendChild(botaoUpdate);
            linha.appendChild(celulaUpdate);

            const celulaDelete = document.createElement('td');
            const botaoDelete = document.createElement('button');
            botaoDelete.classList.add('button');
            botaoDelete.innerText = 'Delete';
            botaoDelete.addEventListener('click', deleteTableEntry.bind(null, tag, index));
            celulaDelete.appendChild(botaoDelete);
            linha.appendChild(celulaDelete);
        }
        dados.appendChild(linha);
        index++;
    }
}

main();
