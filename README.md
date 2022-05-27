# minishell42

Minishell is the 8th project at 42.

It tasks us to create a 'simple' shell. Yes, your little bash or zsh.

<br>

Para voltar ao modo normal, setar em src/EXEC/executor - linha 143 a flag para **false**:<br/><br/>
//TESTE-------------------------- > >>  MEXER AQUI --------------------------<br/>
	int **redirect_out** = **FALSE**;<br/>
//TESTE-----------------------------------------------------------------------<br/>
  
### Entendendo a estrutura:

![redir](./redirects.png)</br></br>

- Exit funciona em modo sem redirect > ok
(N funciona com redirect.)

## Data struct: argve
![argve](./argve.png)</br></br>

(Lembrar cd cmd)
