print("-----Validador de CPF-----")

cpfdigitado = input("Digite o CPF: ")\
    .replace('.', '')\
    .replace('-', '')\
    .replace(' ', '')


if not cpfdigitado.isdigit() or len(cpfdigitado) != 11:
    print("CPF INVÁLIDO!! Formato incorreto (Por favor, digite 11 dígitos!).")
    exit()

cpf1 = cpfdigitado[:9]
contador = 10
soma = 0


for digito in cpf1:
    soma += int(digito) * contador
    contador -= 1

soma = (soma * 10) % 11
if soma == 10:
    soma = 0

if int(cpfdigitado[9]) != soma:
    print("CPF INVÁLIDO!! Primeiro dígito incorreto.")
    exit()

cpf2 = cpfdigitado[:10]
contador_2 = 11
soma_2 = 0

for digito_2 in cpf2:
    soma_2 += int(digito_2) * contador_2
    contador_2 -= 1

soma_2 = (soma_2 * 10) % 11
if soma_2 == 10:
    soma_2 = 0

# Verifica o segundo dígito
if int(cpfdigitado[10]) != soma_2:
    print("CPF INVÁLIDO!! Segundo dígito incorreto.")
    exit()

print(f"{cpfdigitado} é válido!!")
print(f"O primeiro dígito do CPF é {soma}")
print(f"O segundo dígito do CPF é {soma_2}")
