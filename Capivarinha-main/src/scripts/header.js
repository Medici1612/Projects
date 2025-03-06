function main() {
    const logo = document.querySelector('#logo');
    const titulo = document.querySelector('#haze');

    logo?.addEventListener('click', () => {
        window.location.href = 'tela_jogos.html';
    });

    titulo?.addEventListener('click', () => {
        window.location.href = 'tela_jogos.html';
    });
}

main();
