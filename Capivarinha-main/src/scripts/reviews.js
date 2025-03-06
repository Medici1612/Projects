function onClick(event) {
    event.preventDefault();

    const tag = document.querySelector('#review').getAttribute('data-tag');
    const estrelas = document.querySelector('#review input[name="estrelas"]:checked').value;
    const comentario = document.querySelector('#review #comentario').value;

    let reviews = JSON.parse(localStorage.getItem(tag)) || [];

    const review = {
        Estrelas: estrelas,
        Comentario: comentario
    };

    reviews.push(review);

    localStorage.setItem(tag, JSON.stringify(reviews));
    alert('Avaliação feita com sucesso');
    window.location.reload();
}

function main() {
    const button = document.querySelector('#review button');

    button.addEventListener('click', e => onClick(e));
}

main();
