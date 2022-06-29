
function entrar() {

    let email = document.querySelector('#email')
    let senha = document.querySelector('#senha')
    let nome = document.querySelector('#usuarioIndex')

    let listaUser = []
    
    let userValid = {
      email: '',
      senha: '',
      nome: ''
    }
    
    listaUser = JSON.parse(localStorage.getItem('listaUser'))

    listaUser.forEach((item) => {
      if(email.value == item.emailCad && senha.value == item.senhaCad){
         
        userValid = {
           email: item.emailCad,
           senha: item.senhaCad,
           nome: item.nomeCad

         }
         window.location.href="index_.html"
      }
    })

}