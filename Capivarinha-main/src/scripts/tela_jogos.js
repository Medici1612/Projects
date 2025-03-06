const profileButton = document.getElementById('profileButton');
const profileMenu = document.getElementById('profileMenu');

// Alternar exibição do menu
profileButton.addEventListener('click', () => {
    profileMenu.style.display = profileMenu.style.display === 'block' ? 'none' : 'block';
});

// Fechar o menu ao clicar fora dele
window.addEventListener('click', (event) => {
    if (event.target !== profileButton && !profileMenu.contains(event.target)) {
        profileMenu.style.display = 'none';
    }
});
