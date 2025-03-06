// Cores da roleta
const ClasseCSS = {
    PRETO: 'preto',
    VERMELHO: 'vermelho',
    ESPECIAL: 'especial'
};

// Informação de número e cores dos triangulos da roleta
const triangulos = [
    { numero: 0, classe: ClasseCSS.ESPECIAL },
    { numero: 32, classe: ClasseCSS.VERMELHO },
    { numero: 15, classe: ClasseCSS.PRETO },
    { numero: 19, classe: ClasseCSS.VERMELHO },
    { numero: 4, classe: ClasseCSS.PRETO },
    { numero: 21, classe: ClasseCSS.VERMELHO },
    { numero: 2, classe: ClasseCSS.PRETO },
    { numero: 25, classe: ClasseCSS.VERMELHO },
    { numero: 17, classe: ClasseCSS.PRETO },
    { numero: 34, classe: ClasseCSS.VERMELHO },
    { numero: 6, classe: ClasseCSS.PRETO },
    { numero: 27, classe: ClasseCSS.VERMELHO },
    { numero: 13, classe: ClasseCSS.PRETO },
    { numero: 36, classe: ClasseCSS.VERMELHO },
    { numero: 11, classe: ClasseCSS.PRETO },
    { numero: 30, classe: ClasseCSS.VERMELHO },
    { numero: 8, classe: ClasseCSS.PRETO },
    { numero: 23, classe: ClasseCSS.VERMELHO },
    { numero: 10, classe: ClasseCSS.PRETO },
    { numero: 5, classe: ClasseCSS.VERMELHO },
    { numero: 24, classe: ClasseCSS.PRETO },
    { numero: 16, classe: ClasseCSS.VERMELHO },
    { numero: 33, classe: ClasseCSS.PRETO },
    { numero: 1, classe: ClasseCSS.VERMELHO },
    { numero: 20, classe: ClasseCSS.PRETO },
    { numero: 14, classe: ClasseCSS.VERMELHO },
    { numero: 31, classe: ClasseCSS.PRETO },
    { numero: 9, classe: ClasseCSS.VERMELHO },
    { numero: 22, classe: ClasseCSS.PRETO },
    { numero: 18, classe: ClasseCSS.VERMELHO },
    { numero: 29, classe: ClasseCSS.PRETO },
    { numero: 7, classe: ClasseCSS.VERMELHO },
    { numero: 28, classe: ClasseCSS.PRETO },
    { numero: 12, classe: ClasseCSS.VERMELHO },
    { numero: 35, classe: ClasseCSS.PRETO },
    { numero: 3, classe: ClasseCSS.VERMELHO },
    { numero: 26, classe: ClasseCSS.PRETO },
]

// Função que cria a roleta
function criarRoleta(roleta) {
    const raio = 250;
    const angulo = Math.PI * 2 / triangulos.length;

    roleta.style.setProperty('--js-roleta-raio', `${raio}px`);
    roleta.style.setProperty('--js-base', `${raio * Math.tan(angulo / 2) + 1}px`);

    for (const [index, triangulo] of triangulos.entries()) {
        // Criando um dos triangulos da roleta
        const div = document.createElement('div');
        div.classList.add('triangulo');

        // Estilizando o triangulo na roleta
        div.style.rotate = `${angulo * index}rad`;      // Calculando a rotação do triângulo para formar o círculo
        div.classList.add(triangulo.classe);
        // div.style.setProperty('--js-color', valor.cor); // Atualizando a cor do triângulo

        // Criando label com o número do triangulo
        const label = document.createElement('span');
        label.classList.add('triangulo-label');
        label.textContent = triangulo.numero;
        
        // Adicionando o label e o triangulo na tela
        div.appendChild(label);
        roleta.appendChild(div);
    }
}

function main() {
    const roleta = document.querySelector('#roleta');

    criarRoleta(roleta);
}

main();
