import java.util.Scanner;

public class Main
 {
    public static void main(String[] args) throws Exception {
        
        Scanner sc = new Scanner(System.in);
        System.out.println("Seja bem vindo(a) à Calculadora!\n\nAqui serão realizados cálculos em cima de um vetor. O vetor é:");

        int vetorSoma[] = {20,30,40,50};

        for(int i = 0; i<vetorSoma.length; i++){
            System.out.println(vetorSoma[i]);
        }

        System.out.println("Digite qual operação você deseja realizar(-, +, *):");
        char escolha = sc.next().charAt(0);

        if (escolha != '+' && escolha!= '-' && escolha!= '*') {
           System.out.println("Ocorreu um Erro! Essa operação não existe.");
           System.exit(1);
        }

        Calculadora c1 = new Calculadora(vetorSoma, escolha);

        System.out.println(c1.getResult());

        sc.close();
    }
}