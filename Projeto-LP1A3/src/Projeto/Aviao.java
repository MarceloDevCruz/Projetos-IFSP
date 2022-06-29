package Projeto;

public class Aviao extends Aeronave {
	
	public Passageiro[][] lugares;
	
	public Aviao(String modelo, int assento, int fileira) {
		super(modelo);
		lugares = new Passageiro[assento][fileira];
	}
	
	public Passageiro getPassageiro(int assento, int fileira) {
		return lugares[assento][fileira];
	}
	
	public void setPassageiro (int assento, int fileira, Passageiro passageiro) {
		lugares[assento][fileira] = passageiro;
	}
	
	public boolean verificaLugarOcupado (int assento, int fileira) {
		
		if (lugares[assento][fileira] != null) 
		return true;
		else 
			return false;	
	}
	
	public String toString() {
		return modelo;
	}
}
	
