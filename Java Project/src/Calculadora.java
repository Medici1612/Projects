public class Calculadora {
    private int[] vetorOperacao;
    
    private int resultado;
    
    
        public Calculadora(int[] vetorOperacao, char op) {
            this.vetorOperacao = vetorOperacao;
        
    
            switch(op){
                case '+':
                System.out.println("Calculadora - Soma");
                soma();
                break;
                case '-':
                System.out.println("Calculadora - Subtração");
                sub();
                break;
                case '*':
                System.out.println("Calculadora - Multiplicação");
                mult();
            }
            
        }
    
        
        
        private void soma(){
            System.out.println("A soma dos valores do vetor é:");
            for(int i=0;i<this.vetorOperacao.length;i++){
                this.resultado+=vetorOperacao[i];
            }
            
        }
        private void sub(){
            System.out.println("A subtração dos valores do vetor (em relação ao 0) é:");
            for(int i=0;i<this.vetorOperacao.length;i++){
                this.resultado-=vetorOperacao[i];
            }
            
        }
    
        private void mult(){
            System.out.println("A multiplicação dos valores do vetor é:");
            this.resultado = this.vetorOperacao[0];
            for(int i=1;i<this.vetorOperacao.length;i++){
                this.resultado*=vetorOperacao[i];
            }
            
        }
        
        
        public int getResult(){
            return this.resultado;
        }
    }
