package Projeto;
import javax.swing.*;

public class main {
	
	public static void main(String[] args) {
		
		int 	opc_0, opc_1, opc_2;
		int 	fileira, assento, numeroVoo, numeroAeronave;
		String  modelo, data, hora, nomePassageiro, CPF;
		String  auxiliar= "", reservaMensagem = "", reservaRealizadas="";
		Aviao[] aeronave = new Aviao[10];
		Voo[]   voo = new Voo[10];
		int     aeroQtd = 0, vooQtd = 0;
				
		try {
			do {
				opc_0 = Integer.parseInt(JOptionPane.showInputDialog(
				          "Menu Principal"
						+ "\n     1. Parâmetros do Sistema"
						+ "\n     2. Reserva de Passagens"
						+ "\n     3. Sair"
						));
				
				switch(opc_0) {
				case 1 : 		
					try {
					do {
						opc_1 = Integer.parseInt(JOptionPane.showInputDialog(
						          "Parâmetros do Sistema"
								+ "\n     1. Cadastrar Aeronave"
								+ "\n     2. Cadastrar Voo"
								+ "\n     3. Voltar"
								));
						
						switch(opc_1) {
						
						case 1 :
							try {
								
								if (aeroQtd < aeronave.length) {
									
							modelo  = JOptionPane.showInputDialog("Informe o modelo da Aeronave");
							fileira = Integer.parseInt(JOptionPane.showInputDialog("Informe o número de Assentos por fileira da Aeronave " + modelo));
							assento = Integer.parseInt(JOptionPane.showInputDialog("Informe o número de fileira da Aeronave " + modelo));
							
							aeronave[aeroQtd] = new Aviao(modelo,assento,fileira);
							aeroQtd++;
							
							JOptionPane.showMessageDialog(null, "Uma nova Aeronave foi cadastrada\n"
									+ modelo + "\nCom " + fileira + " Assentos e " + assento + " Fileiras");
								}
								
								else
									JOptionPane.showMessageDialog(null, "Quantidade de aeronaves cadastradas excedidas");
							}
							
							catch(Exception error) {
								
								JOptionPane.showMessageDialog(null, "Ocorreu o erro " + error.getMessage());	
							}
							break;
							
						case 2 :
						try {
						
							if (vooQtd < voo.length) {
								
								auxiliar = mensagemZerar();
								for (int i=0; i < aeronave.length ; i++) {
									if ( aeronave[i] != null)
									auxiliar = auxiliar + i + ". " + aeronave[i].getModelo() + "\n";
								}
								
						numeroAeronave = Integer.parseInt(JOptionPane.showInputDialog(""
								+ "Escolha em qual Modelo de Aeronave deseja cadastrar o Voo!\n\n"
								+ auxiliar));
						
						numeroVoo = Integer.parseInt(JOptionPane.showInputDialog("Informe o número do voo"));
						data      = JOptionPane.showInputDialog("Informe a data do Voo");
						hora      = JOptionPane.showInputDialog("Informe o a hora do Voo");	
						
						voo[vooQtd] = new Voo(aeronave[numeroAeronave], numeroVoo, data, hora);
			
						JOptionPane.showMessageDialog(null, "Novo voo cadastrado!\n"
								+ aeronave[numeroAeronave].modelo + "\nVoo: " + numeroVoo + "\nData: " + data + "\nHorário: " + hora);
								vooQtd++;
							}
						
						else 
							JOptionPane.showMessageDialog(null, "Quantidade de Voos cadastradas excedidas");
						
						}
						
						catch(Exception error) {
							
							JOptionPane.showMessageDialog(null, "Ocorreu o erro " + error.getMessage());	
						}
						break;

						}
					}
					while(opc_1 != 3);
				}
					
				catch (Exception error) {
					JOptionPane.showMessageDialog(null, "Ocorreu o erro " + error.getMessage());
				}
			    break;
			    
				case 2 :
					try {
					do {
						opc_2 = Integer.parseInt(JOptionPane.showInputDialog(
						          "Reserva de Passagens"
								+ "\n     1. Fazer Reserva"
								+ "\n     2. Consultar Lugares Vazios"
								+ "\n     3. Consultar Reservas Realizadas"
								+ "\n     4. Voltar"
								));
						
						switch(opc_2) {
						
						case 1 : 				
							
							try {
								
								numeroAeronave = Integer.parseInt(JOptionPane.showInputDialog(""
								+ "Escolha em qual Aeronave deseja fazer uma reserva!\n\n"
								+ auxiliar));
								fileira = Integer.parseInt(JOptionPane.showInputDialog("Escolha o Assento "));
								assento = Integer.parseInt(JOptionPane.showInputDialog("Escolha a Fileira "));
								nomePassageiro = JOptionPane.showInputDialog("Digite o nome do passageiro");
								CPF = JOptionPane.showInputDialog("Digite o CPF passageiro");
								Passageiro passageiro = new Passageiro(nomePassageiro, CPF);
								aeronave[numeroAeronave].setPassageiro(assento, fileira, passageiro);
								JOptionPane.showMessageDialog(null,"Reserva feita com sucesso!\n" + 
								aeronave[numeroAeronave] + "\nAssento: " + fileira + ", Fileira: " + assento
								+ "\nNome: " + nomePassageiro + ", CPF: " + CPF);
							}
							
							catch(Exception error) {
								JOptionPane.showMessageDialog(null, "Ocorreu o erro " + error.getMessage());
							}
						break;
						
						case 2 :
							
							try {
								numeroAeronave = Integer.parseInt(JOptionPane.showInputDialog(""
										+ "Escolha em qual Aeronave consultar reservas realizadas\n\n"
										+ auxiliar));
								for(int i=0; i < aeronave[numeroAeronave].lugares.length; i++) {
									for(int j=0; j < aeronave[numeroAeronave].lugares[i].length; j++) {
										if( aeronave[numeroAeronave].verificaLugarOcupado(i,j)) {
											reservaRealizadas += "(X) ";
									}
										else {
											reservaRealizadas += "(  ) ";
										}	
								}
									reservaRealizadas +="\n";
								}
								JOptionPane.showMessageDialog(null, reservaRealizadas);
								reservaRealizadas = mensagemZerar();
							}
							catch(Exception error) {
								JOptionPane.showMessageDialog(null, "Ocorreu o erro " + error.getMessage());
							}
						break;
							
						case 3 : 
							
							try {
								numeroAeronave = Integer.parseInt(JOptionPane.showInputDialog(""
										+ "Escolha em qual Aeronave consultar reservas realizadas\n\n"
										+ auxiliar));
								reservaMensagem = mensagemZerar();
								for(int i=0; i < aeronave[numeroAeronave].lugares.length; i++) {
									for(int j=0; j < aeronave[numeroAeronave].lugares[i].length; j++) {
										if(aeronave[numeroAeronave].verificaLugarOcupado(i,j)) {
											Passageiro passageiro = aeronave[numeroAeronave].getPassageiro(i,j);
											reservaMensagem = "[Fileira " + i + ", Assento " + j + "] - " +
											passageiro.getNome() + " - " + passageiro.getCPF() +
											"\n";
											
										}
									}
								}
								JOptionPane.showMessageDialog(null, "Reservas feitas:\n"
										+ reservaMensagem);
							}
							catch(Exception error) {
								JOptionPane.showMessageDialog(null, "Ocorreu o erro " + error.getMessage());
							}
						break;
				
						}
					}
					while(opc_2 != 4);
				}
				catch (Exception error) {
					JOptionPane.showMessageDialog(null, "Ocorreu o erro " + error.getMessage());
				}
				break;
				
				case 3 :                       break;
				default: algoValidoMensagem(); break;	
				}
			}
			while(opc_0 != 3);
		}
		catch (Exception error) {
			JOptionPane.showMessageDialog(null, "Ocorreu o erro " + error.getMessage());
		}
	}
	
	
	private static String mensagemZerar() {
		String zerarString = "";
		return zerarString;
	}
	

	private static void algoValidoMensagem() {
		JOptionPane.showMessageDialog(null, "Digite algo válido");
		}
}
