let anuncio = []

let anuncioValid = {
    endereco: '',
    CEP: '',
    cidade: '',
    valor: ''
}
    anuncio = JSON.parse(localStorage.getItem("Anuncio"))
    anuncio.forEach((item) => {
    anuncioValid = {
        endereco: item.enderecoCad,
        CEP: item.CEPCad,
        cidade: item.cidadeCad,
        valor: item.valorCad
    }

})

let endereco = anuncioValid.endereco
let valor = anuncioValid.valor
let cidade = anuncioValid.cidade
let CEP = anuncioValid.CEP

document.getElementById('Cadendereco').innerHTML = endereco
document.getElementById('Cadvalor').innerHTML = valor
document.getElementById('Cadcidade').innerHTML = cidade
document.getElementById('CadCEP').innerHTML = CEP

function removerItem () {
    localStorage.removeItem('Anuncio')
    window.location.href='apartamentos.html'
}