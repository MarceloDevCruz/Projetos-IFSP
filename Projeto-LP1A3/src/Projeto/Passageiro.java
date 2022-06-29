package Projeto;

public class Passageiro {
	
	private String nome;
	private String CPF;
	
	public Passageiro (String nome, String CPF) {
		setNome(nome);
		setCPF(CPF);
	}
	
	public String getNome() {
		return nome;
	}
	
	public String getCPF() {
		return CPF;
	}


	public void setNome(String nome) {
		this.nome = nome;
	}


	public void setCPF(String CPF) {
		this.CPF = CPF;
	}

}
