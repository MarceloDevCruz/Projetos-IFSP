const button = document.getElementById('buttonAnunciar');
const endereco = document.getElementById('endereco');
const CEP = document.getElementById('CEP');
const cidade = document.getElementById('cidade');
const valor = document.getElementById('valor');


button.addEventListener('click', function onClick() {

        let Anuncio = JSON.parse(localStorage.getItem('Anuncio') || '[]')

      Anuncio.push(
      {
        enderecoCad: endereco.value,
        CEPCad: CEP.value,
        cidadeCad: cidade.value,
        valorCad: valor.value
      }
      )


      localStorage.setItem('Anuncio', JSON.stringify(Anuncio))
      window.location.href='index_.html'
})
