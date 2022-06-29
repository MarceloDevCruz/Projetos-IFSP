
const button = document.getElementById('button');
const nome = document.getElementById('nome');
let validNome = false;
const senha = document.getElementById('senha');
let validSenha = false;
const email = document.getElementById('email');
let validEmail = false;

nome.addEventListener('keyup', () => {
    if(nome.value != "" && nome.value.length > 3)
    validNome = true;
})

senha.addEventListener('keyup', () => {
    if(senha.value != "" && senha.value.length > 3)
    validSenha = true;
})

email.addEventListener('keyup', () => {
    if(email.value.indexOf("@")!=-1 && email.value.indexOf(".") != -1)
    validEmail = true;
})

/*Cadastrar um usuário */
button.addEventListener('click', function onClick() {
    if(validNome && validSenha && validEmail) {
        let listaUser = JSON.parse(localStorage.getItem('listaUser') || '[]')
      
      listaUser.push(
      {
        nomeCad: nome.value,
        emailCad: email.value,
        senhaCad: senha.value
      }
      )
      localStorage.setItem('listaUser', JSON.stringify(listaUser))
      window.location.href='login.html'
    }
})
