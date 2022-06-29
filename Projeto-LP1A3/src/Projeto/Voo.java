package Projeto;

public class Voo  {
	
	private Aviao aeronave;
	private int numero;
	private String data;
	private String hora;
	
	public Voo (Aviao aeronave, int numero, String data, String hora) {
		this.aeronave = aeronave;
		this.numero = numero;
		this.data = data;
		this.hora = hora;
	}
	
	
	public int getNumero() {
		return numero;
	}
	
	public String getData() {
		return data;
	}
	
	public String getHora() {
		return hora;
	}

}
