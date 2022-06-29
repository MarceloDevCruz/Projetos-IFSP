package Projeto;

public class Aeronave {
	
	protected String modelo;

	
	// Construtor Aeronave //
	public Aeronave (String modelo) {
		setModelo(modelo);
	}
	
	
	// GET MODELO //
	public String getModelo () {
		return modelo;
	}
	
	// SET MODELO //
	public void setModelo (String modelo) {
		this.modelo = modelo;
	}
	
	
}
