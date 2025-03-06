
function logoffEvent() {
    localStorage.removeItem('sessao');
    window.location.reload();
}

function main() {
    const logofflink = document.querySelector('#logoff');

    logofflink.addEventListener('click', logoffEvent);
}

document.addEventListener('DOMContentLoaded', main);
