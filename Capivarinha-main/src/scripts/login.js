function showSuccessMessage(message) {
    const successMessage = document.createElement('div');
    successMessage.textContent = message;
    successMessage.style.position = 'fixed';
    successMessage.style.top = '10px';
    successMessage.style.right = '10px';
    successMessage.style.backgroundColor = '#4CAF50';
    successMessage.style.color = '#fff';
    successMessage.style.padding = '10px';
    successMessage.style.borderRadius = '5px';
    successMessage.style.boxShadow = '0 2px 4px rgba(0, 0, 0, 0.2)';
    successMessage.style.zIndex = '1000';
    document.body.appendChild(successMessage);

    setTimeout(() => {
        successMessage.remove();
    }, 3000);
}

function showMessage(message, type = 'error') {
    alert(`${type === 'error' ? 'Erro:' : 'Sucesso:'} ${message}`);
}

function loginSubmitEvent(event) {
    event.preventDefault();

    const email = document.getElementById('email').value;
    const password = document.getElementById('password').value;

    // Verificação de login de administrador
    if (email === 'admin' && password === 'admin') {
        localStorage.setItem('sessao', JSON.stringify({
            Nome: 'admin',
            Email: 'admin',
            Senha: 'admin'
        }));
        showSuccessMessage('Login como administrador bem-sucedido!');
        setTimeout(() => {
            window.location.href = '../public/tela_jogos.html'; // Página de administração
        }, 500);
        return;
    }

    // Verificação de usuários normais
    const users = JSON.parse(localStorage.getItem('users') ?? '[]') || [];

    const user = users.find(user => user.Email === email && user.Senha === password);

    if (!user) {
        showMessage('E-mail/Usuário ou senha incorretos.');
        return;
    }

    localStorage.setItem('sessao', JSON.stringify(user));

    showSuccessMessage(`Bem-vindo, ${user.Nome}!`);
    event.target.reset();

    document.getElementById('loginModal').style.display = 'none';
    setTimeout(() => {
        window.location.href = '../public/tela_jogos.html'; // Tela de jogos
    }, 500);
}

function registerSubmitEvent(event) {
    event.preventDefault();

    const username = document.getElementById('username').value;
    const email = document.getElementById('registerEmail').value;
    const password = document.getElementById('registerPassword').value;

    const users = JSON.parse(localStorage.getItem('users') ?? '[]') || [];

    if (users.some(x => x.Email == email)) {
        showMessage('E-mail já cadastrado');
        return;
    }

    users.push({
        Nome: username,
        Email: email,
        Senha: password
    });

    console.log()

    localStorage.setItem('users', JSON.stringify(users));

    showSuccessMessage(`Cadastrado com sucesso!`);

    document.getElementById('registerModal').style.display = 'none';
}

document.addEventListener('DOMContentLoaded', () => {
    const loginForm = document.getElementById('loginForm');
    const registerForm = document.getElementById('registerForm');

    if (loginForm) {
        loginForm.addEventListener('submit', loginSubmitEvent)
    }

    if (registerForm) {
        registerForm.addEventListener('submit', registerSubmitEvent)
    }
});
