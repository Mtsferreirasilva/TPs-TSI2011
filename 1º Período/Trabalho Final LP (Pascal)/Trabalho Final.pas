Program Trabalho;
uses crt,dos;
{===================================TYPE======================================}
type TReg_Func = record
                  matricula,codigoDepartamento:integer;
                  nome:string[30];
                  salario : real;
                  DataContratacao:string[10];
                  DataNascimento:string[10];
                  CPF:string[11];
                  Rua,bairro,cidade,estado,email,complemento:string[30];
                  numero:string;
                end;

      TReg_Dep = record
                  codigo,codigoGerente:integer;
                  nome:string[30];
                  ramal:string[6];
                end;

       TReg_Hist_Sal = record
                         matricula:integer;
                         salario:real;
                         mes,ano:word;{inteiro sem sinal}
                       end;

      TReg_Hist_Func = record
                  matricula,codigoDepartamento:integer;
                  data:string[10];
                end;

      TReg_Hist_Dep = record
                       codigoDepartamento,codigoGerente:integer;
                       data:string[10];
                      end;

     TArq_Dep=file of TReg_Dep;
     TArq_Func=file of TReg_Func;
     TArq_Hist_Sal = file of  TReg_Hist_Sal;
     TArq_Hist_Func = file of TReg_Hist_Func;
     TArq_Hist_Dep = file of TReg_Hist_Dep;

{========================================VAR================================}
var ArqDep:TArq_Dep;
    ArqFunc:TArq_Func;
    ArqHistSal : TArq_Hist_Sal;
    ArqHistFunc : TArq_Hist_Func;
    ArqHistDep : TArq_Hist_Dep;
    op,x,y,cor:integer;
    tecla:char;
    dia, mes, ano, diasem: word;
    data2:string;
  {  hora, min, seg, mili: word;  } { Caso usar GETTIME }
{====================== Mudar cor do menu ====================================}
procedure mudacor;
begin
	textbackground(black);
	textcolor(8);
end;

procedure voltacor;
begin
	textcolor(white);
	textbackground(black);
end;

procedure mudarcorsair(var cor:integer);
begin
     cor:=8;
end;

procedure voltarcorsair(var cor:integer);
begin
     cor:=14;
end;

{==============TRANSFORMAR DIA,MES E ANO EM UMA UNICA STRING DATA=============}

function pegardata (dia,mes,ano:word):string;

var d,m,a:string;

begin
     str(dia,d);
     str(mes,m);
     str(ano,a);
     pegardata:=d+'/'+m+'/'+a;
end;


{=======================Borda do menu principal ==============================}
procedure borda();
var
  i:integer;
begin
     for i:=15 to 65 do
       begin
         gotoxy(i,3);
         writeln(chr(205));
         gotoxy(i,22);
         writeln(chr(205));
       end;
     for i:=4 to 21 do
       begin
         gotoxy(14,i);
         writeln(chr(186));
         gotoxy(66,i);
         writeln(chr(186));
       end;
         gotoxy(14,3);
         writeln(chr(201));
         gotoxy(66,3);
         writeln(chr(187));
         gotoxy(14,22);
         writeln(chr(200));
         gotoxy(66,22);
         writeln(chr(188));
end;

{==================Verifica existÍncia de MES e ANO==========================}
function verificaMes(m : integer):boolean;
begin
     if (m < 1) or (m > 12) then
        verificaMes:= false
     else
        verificaMes:= true;
end;
{-------ano}
function verificaAno(A : integer):boolean;
begin
     if (A < 1896) or (A > 2011) then
        verificaAno:= false
     else
        verificaAno:= true;
end;

{=PESQUISA NO HISTORICO DE SALARIO POR MES INICIAL,FINAL e ANO INICIAL,FINAL=}

function PesSalPeriodo(var ahs:TArq_Hist_Sal; mI,mF,aI,aF,matricula:integer):boolean ;
 var  i,posicao,k:integer;
      r:TReg_Hist_Sal;
 begin
      seek(ahs,0);
      posicao:=0;
      i:=12;
      while not eof(ahs) do
      begin
        seek(ahs,posicao);
        read(ahs,r);
        if matricula = r.matricula then
        begin
          if (r.ano > aI) and (r.ano< aF )then
          begin
            gotoxy(26,i);
            writeln(r.mes,'/',r.ano,'                R$',r.salario:0:2);
          end
          else
          if r.ano = aI then
          begin
            if r.mes>= mF then
            begin
              gotoxy(26,i);
              writeln(r.mes,'/',r.ano,'                R$',r.salario:0:2);
            end;
            end
            else
              if r.ano=aF then
              begin
                if r.mes<=mF then
                 begin
                  gotoxy(26,i);
                  writeln(r.mes,'/',r.ano,'                R$',r.salario:0:2);
                 end;
              end;
            i:=i + 1;
            readkey;
          end;
          posicao:=posicao+1;
          {Apagando informaÁıes anteriores}
                 if i = 19 then
                    for k := 11 to 19 do
                      begin
                        gotoxy(16,k);
                        writeln('                                                ');
                        i:=12;
                      end;
      end;
            if not eof(ahs) then
               PesSalPeriodo:= true
            else
                PesSalPeriodo:=false;
 end;

{====================================VALIDA CPF=============================}
{CONJUNTO DE CONTAS PARA VERIFICAR A EXISTENCIA REAL DO CPF}
function valida_cpf(cpf:string) :boolean;
var
   i, status, int, somacpf, j:integer;
   num:string;
   final:real;
   cpf_v: array [1..11] of integer;
   ok:boolean;
begin
     i:=1;
     ok:= true;
     while (i <= 11) and ok do
         begin
         		somacpf:=0;
              { CONVERTENDO OS CARACTERES PARA INTEIROS }
              num:=cpf[i];
              val(num, int, status);
              if status = 0 then
                  cpf_v[i]:= int
              else
                  ok:= false;

              { PRIMEIRO DIGITO VERIFICADOS }
              if (i = 10) and ok then
                 begin
                      if ok then
                         for j:=2 to 10 do
                             somacpf:=somacpf + cpf_v[11-j] * j;

                      final:= somacpf mod 11;
                      if final < 2 then
                         begin
                              if cpf_v[i] <> 0 then
                                 ok:= false;
                         end
                      else
                          begin
                               somacpf:= abs(somacpf mod 11 - 11);
                               if cpf_v[i] <> somacpf then
                                  ok:= false;
                          end;
                 end;

              { SEGUNDO DIGITO VERIFICADOS }
              if (i = 11) and ok then
                 begin
                      if ok then
                         for j:=2 to 11 do
                             somacpf:=somacpf + cpf_v[12-j] * j;

                      final:= somacpf mod 11;
                      if final < 2 then
                         begin
                              if cpf_v[i] <> 0 then
                                 ok:= false;
                         end
                      else
                          begin
                               somacpf:= 11 -(somacpf mod 11);
                               if cpf_v[i] <> somacpf then
                                  ok:= false;
                          end;
                 end;
              i:=i+1;
         end;
     if ok then
     	valida_cpf:= true
     else
     	valida_cpf:= false;
end;

{=============================VALIDA EMAIL===================================}
function validaemail(email:string):boolean;
var tamanho,i,ocorrencias:integer;
begin
     tamanho:=length(email);
     ocorrencias:=0;
     for i:=1 to tamanho do
          if email[i]='@' then
           begin
                ocorrencias:=ocorrencias + 1;
           end;
     if ocorrencias <> 1 then
        validaemail:= false
     else
         validaemail:=true;

end;

{===========================VALIDA ESTADOS ==================================}
procedure estados(est:string; var achou:boolean);
begin
 if (est ='SP') then
  achou:=true
 else
 if (est ='RJ') then
  achou:=true
 else
 if (est ='ES') then
  achou:=true
 else
 if (est ='MG') then
  achou:=true
 else
 if (est ='BA') then
  achou:=true
 else
 if (est ='SE') then
  achou:=true
 else
 if (est ='PE')then
  achou:=true
 else
 if (est ='AL') then
  achou:=true
 else
 if (est ='PB') then
  achou:=true
 else
 if (est ='RN') then
  achou:=true
 else
 if (est ='CE') then
  achou:=true
 else
 if (est ='PI') then
  achou:=true
 else
 if (est ='MA') then
  achou:=true
 else
 if (est ='PA') then
  achou:=true
 else
 if (est ='AM') then
  achou:=true
 else
 if (est ='AP') then
  achou:=true
 else
 if (est ='RR') then
  achou:=true
 else
 if (est ='AC') then
  achou:=true
 else
 if (est ='DF') then
  achou:=true
 else
 if (est ='TO') then
  achou:=true
 else
 if (est ='MT') then
  achou:=true
 else
 if (est ='MS') then
  achou:=true
 else
 if (est ='RO') then
  achou:=true
 else
 if (est ='PR') then
  achou:=true
 else
 if (est ='SC') then
  achou:=true
 else
 if (est ='RS') then
  achou:=true
 else
  achou:=false;
end;

{===================================VALIDA NOME=============================}
function nome(n:string):boolean;
var tamanho:integer;
    i,ocorrencias:integer;
begin
     tamanho:=length(n);
     ocorrencias:=0;
     for i:=1 to tamanho do
        if n[i] = ' ' then
           ocorrencias := ocorrencias + 1 ;

     if ocorrencias = tamanho then
        nome:=false
     else
        nome:=true;
end;



{====================================DATA===================================}
{ê ACEITO APENAS DATAS NO FORMADO DD/MM/AAAA, CASO CONTRARIO DATA := FALSE }
function data(x:string):boolean;
var dia, mes, ano, erro: integer;
    dias, mess, anos:string;
begin
 if (x[3]='/') and (x[6]='/') then
 begin
  dias:=x[1];
  dias:=dias+x[2];
  mess:=x[4];
  mess:=mess+x[5];
  anos:=x[7];
  anos:=anos+x[8];
  anos:=anos+x[9];
  anos:=anos+x[10];
  val(dias,dia,erro);
  val(mess,mes,erro);
  val(anos,ano,erro);
  if erro=0 then
  begin
  if (ano <= 1992) or (ano <1896)  then
  begin
   case mes of
   1,3,5,7,8,10,12: if (dia>0) and (dia<=31) then
                     data:=true
                    else
                    begin
                     data:=false;
                    end;

   2:begin
     if (ano mod 100<>0) and (ano mod 4=0) or (ano mod 400=0) then
     if (dia>0) and (dia<=29) then
      data:=true
     else
     begin
      data:=false;
     end
     else
     if (dia>0) and (dia<=28) then
      data:=true
     else
     begin
      data:=false;
     end;
     end;
   4,6,9,11: if (dia>0) and (dia<=30) then
              data:=true;
             else
             begin
              data:=false;
             end;
   end;
  end
  else
  begin
   data:=false;
  end;
 end
 else
 begin
  data:=false;
 end;
 if (ano = 1992) then
    begin
         if (mes > 6) then
            data:=false;
         if (mes = 6) and (dia > 20) then
            data:=false;
    end;
 end
 else
     begin
          data:=false;
     end;{End de Verificando ano 1992}
end;


{=================VERIFICA DEPARTAMENTO COM DETERMIADO CODIGO================}

function pesquisaDep(var ad:TArq_Dep; codigo:integer):integer;
var R:Treg_Dep;
    posicao:integer;
    achou:boolean;
begin
  seek(ad,0);
  posicao:=0;
  achou := false;

  while not eof(ad) and not achou do
  begin
    read(ad,r);
    if r.codigo = codigo then
      achou := true
    else
      posicao := posicao + 1;
  end;

  if achou then
    pesquisaDep := posicao
  else
    pesquisaDep := -1;
 end;

{===========VERIFICA SE EXISTE FUNCIONARIO PELA MATRICULA ====================}

function pesquisaFunc(var af:TArq_Func; matricula:integer):integer;
var R:Treg_Func;
    posicao:integer;
    achou:boolean;
begin
  seek(af,0);
  posicao:=0;
  achou := false;

  while not eof(af) and not achou do
  begin
    read(af,r);
    if r.matricula = matricula then
      achou := true
    else
      posicao := posicao + 1;
  end;

  if achou then
    pesquisaFunc := posicao
  else
    pesquisaFunc := -1;
 end;
{=============VERIFICA DUPLICIDADE EM ARQUIVO HISTORICO SALARIO ==============}

function pesquisaHistoricoSalario(var HS:TArq_Hist_Sal; matricula,mes,ano:integer):integer;
var R:Treg_Hist_Sal;
    posicao:integer;
    achou:boolean;
begin
  seek(hs,0);
  posicao:=0;
  achou := false;

  while not eof(hs) and not achou do
  begin
    read(hs,r);
    if (r.matricula = matricula) and( r.mes>=mes) and(r.ano=ano)  then
      achou := true
    else
      posicao := posicao + 1;
  end;

  if achou then
    pesquisaHistoricoSalario := posicao
  else
    pesquisaHistoricoSalario := -1;
 end;


 {=============VERIFICA FUNCIONARIO EM HISTORICO DE FUNCIONARIO==============}
{
 function (var hs:TArq_Hist_Sal; matricula:integer):integer;
 begin
 end;
 }
 {===============FAZ PESQUISA DE RELATORIOS DE FUNCIONARIOS==================}
  Function pesquisaRelatorio(var af:TArq_Func; codigo:integer):boolean;
 var i,j,k:integer;
     r:TReg_Func;
     totalsalarios:real;

 begin
      totalsalarios:=0;
      i:=0;
      j:=11;
      for k:=16 to 64 do
      begin
          gotoxy(k,10);
          writeln('-');
      end;
      seek(af,0);
      while not eof(af) do
            begin
                 read(af,r);
                 if r.codigoDepartamento = codigo then
                    begin
                         gotoxy(22,j);
                         writeln(r.matricula);
                         gotoxy(33,j);
                         writeln('|');
                         gotoxy(38,j);
                         writeln(upcase(r.nome));
                         gotoxy(49,j);
                         writeln('|');
                         gotoxy(53,j);
                         writeln('R$ ',r.salario:2:2);
                         j:=j+1;
                         totalsalarios:=totalsalarios + r.salario;
                         readkey;
                    end;
                 i:=i+1;
                 gotoxy(39,23);
                 if eof(af) then
                 begin
                    textcolor(yellow);
                    writeln('Fim');
                 end;
                 {Apagando informaÁıes anteriores}
                 if j = 19 then
                    for k := 11 to 19 do
                      begin
                        gotoxy(16,k);
                        writeln('                                                ');
                        j:=11;
                      end;
             end;
             gotoxy(16,19);
             writeln('Total da Folha de Pagamento: R$',totalsalarios:0:2);


             if not eof(af) then
                pesquisaRelatorio:= true
             else
                 pesquisaRelatorio:=false;
 end;


 {=========================VERIFICA SE H¡ LETRAS EM CAPO =====================}

function procurarletra(nome:string):boolean;
 var
     erro,numero:integer;
 begin
      val(nome,numero,erro);
        if erro <> 0 then
           procurarletra:=false;

 end;

 {===================CADASTRAR DEPARTAMENTO ==================================}

 procedure cadastroDepartamento(var ad:TArq_Dep);
 var r:Treg_Dep;
     sair : char;
     achou:boolean;
 begin
   repeat
     achou:=true;
     clrscr;
     borda();
     textcolor(white);
     gotoxy(30,2);
     writeln('Cadastro de Departamento');
     gotoxy(16,5);
     write('Codigo do Departamento: ');
     readln(r.codigo);
     if pesquisaDep(ad,r.codigo) <> -1 then
     begin
       textcolor(yellow);
       gotoxy(15,23);
       writeln('Codigo Repetido! Pressione uma tecla para continuar');
       readkey;
     end
     else
     begin
       textcolor(white);
       gotoxy(16,6);
       write('Nome Departamento: ');
       readln(r.nome);
       achou:=nome(r.nome);
       if achou then
       begin
         gotoxy(16,7);
         write('Ramal: ');
         readln(r.ramal);
         achou:=procurarletra(r.ramal);
         if achou then
         begin
             gotoxy(16,8);
             write('Codigo do Gerente: ');
             readln(r.codigogerente);
             seek(ad,filesize(ad));
             write(ad,r);
         end
         else
         begin
           textcolor(yellow);
           gotoxy(15,23);
           writeln('Ramal Invalido! Pressione uma tecla para continuar');
           readkey;
         end; {END do RAMAL}
       end
       else
       begin
           textcolor(yellow);
           gotoxy(15,23);
           writeln('Nome Invalido! Pressione uma tecla para continuar');
           readkey;
       end;{END do NOME}
     end;
     textcolor(white);
     gotoxy(32,20);
     write('Deseja sair S/N ');
     sair:= readkey;
     sair:= upcase(sair);
   until sair = 'S';
 end;

 {=========================CADASTRAR FUNCIONARIO ============================}

 procedure cadastroFuncionario(var af:TArq_Func;var ad:TArq_Dep);
 var r:Treg_Func;
     sair : char;
     achou:boolean;
     aux:string[2];
 begin
   repeat
     achou:=true;
     clrscr;
     borda();
     textcolor(white);
     gotoxy(30,2);
     write('Cadastro de Funcionarios');
     gotoxy(16,5);
     write('Codigo Departamento: ');
     readln(r.codigoDepartamento);
     if pesquisaDep(ad,r.codigoDepartamento) = -1 then
     begin
       textcolor(yellow);
       gotoxy(10,23);
       writeln('Departamento Inexistente! Pressione uma tecla para continuar');
       readkey;
     end
     else
     begin
       textcolor(white);
       gotoxy(16,6);
       write('Matricula do Funcionario: ');
       readln(r.matricula);
       if pesquisaFunc(af,r.matricula) <> -1 then
       begin
         textcolor(yellow);
         gotoxy(14,23);
         writeln('Matricula Repetida! Pressione uma tecla para continuar');
         readkey;
       end
       else
       begin
         textcolor(white);
         gotoxy(16,7);
         write('Nome: ');
         readln(r.nome);
       achou:= nome(r.nome);
       if achou then
       begin
         gotoxy(16,8);
         write('Data de Nascimento (DD/MM/AAAA): ');
         readln(r.DataNascimento);
         achou:=data(r.DataNascimento);
         if achou then
         begin
          gotoxy(16,9);
          write('CPF: ');
          readln(r.cpf);
          achou := valida_cpf(r.cpf);
          if achou then
          begin
          gotoxy(16,10);
          write('Rua: ');
          readln(r.rua);
          gotoxy(16,11);
          write('Bairro: ');
          readln(r.bairro);
          gotoxy(16,12);
          write('Numero: ');
          readln(r.numero);
          achou:=procurarletra(r.numero);
          if achou then
          begin
            gotoxy(16,13);
            write('Complemento: ');
            readln(r.complemento);
            gotoxy(16,14);
            write('Cidade: ');
            readln(r.cidade);
            gotoxy(16,15);
            write('Estado (UF): ');
            readln(r.estado);
            aux:=upcase(r.estado);
            estados(aux,achou);
            if achou then
               begin
                 gotoxy(16,16);
                 write('Email: ');
                 readln(r.email);
                 achou:=validaemail(r.email);
                 if achou then
                 begin

                   gotoxy(16,17);
                   write('Salario: R$');
                   readln(r.salario);
                   if r.salario >= 0 then
                   begin
                     seek(af,filesize(af));
                     write(af,r);
                   end
                   else
                   begin
                     textcolor(yellow);
                     gotoxy(14,23);
                     writeln('Salario Invalido! Pressione uma tecla para continuar');
                     readkey;
                   end; {END DO SALARIO}

                 end
                 else
                 begin
                   textcolor(yellow);
                   gotoxy(16,23);
                   writeln('Email Invalido! Pressione uma tecla para continuar');
                   readkey;
                 end;{END DO EMAIL}

               end
               else
               begin
                 textcolor(yellow);
                 gotoxy(14,23);
                 writeln('Estado Invalido! Pressione uma tecla para continuar');
                 readkey;
               end;{END DO ESTADO DEPOIS DO ELSE}
             end
             else
             begin
               textcolor(yellow);
               gotoxy(15,23);
               writeln('Numero Invalido! Pressione uma tecla para continuar');
               readkey;
             end;{END DO NUMERO}
            end
            else
            begin
              textcolor(yellow);
              gotoxy(16,23);
              writeln('CPF invalido! Pressione uma tecla para continuar');
              readkey;
            end;{END do CPF DEPOIS DO ELSE}
         end
         else
         begin
           textcolor(yellow);
           gotoxy(15,23);
           writeln('Data Invalida! Pressione uma tecla para continuar');
           readkey;
         end;{END da DATA DE NASCIMENTO DEPOIS DO ELSE}
       end
       else
       begin
           textcolor(yellow);
           gotoxy(15,23);
           writeln('Nome Invalido! Pressione uma tecla para continuar');
           readkey;
       end;{END do NOME }
     end;
     end;

     textcolor(white);
     gotoxy(32,20);
     write('Deseja sair S/N ');
     sair:= readkey;
     sair:= upcase(sair);
   until sair = 'S';
 end;
 {========================ALTERAR SALARIO DE FUNCIONARIO======================}

 procedure alterarSalario(var AF:Tarq_Func;var HistSal:TArq_Hist_Sal);
 var r:Treg_func;
     posicao:integer;
     rh : TReg_Hist_Sal;
     sair:char;
 begin
   repeat
     clrscr;
     borda();
     textcolor(white);
     gotoxy(25,2);
     write('Alterar Salario de Funcionario');
     gotoxy(16,5);
     write('Matricula: ');
     readln(r.matricula);
     posicao := pesquisaFunc(af,r.matricula);
     if posicao = -1 then
     begin
       textcolor(yellow);
       gotoxy(13,23);
       writeln('Matricula Inexistente! Pressione uma tecla para continuar');
       readkey;
     end
     else
     begin
       seek(af,posicao);
       read(af,r);
       repeat
         textcolor(white);
         gotoxy(16,6);
         write('Novo Salario: ');
         readln(r.salario);
         if r.salario <= 0 then
         begin
           textcolor(yellow);
           gotoxy(15,23);
           writeln('Valor Incorreto! Pressione uma tecla para continuar');
           readkey;
         end;
       until r.salario>0;
       rh.matricula := r.matricula;
       rh.salario := r.salario;
       textcolor(white);
       gotoxy(16,7);
       write('Mes: ');
       readln(rh.mes);
       if verificaMes(rh.mes) then
       begin
         gotoxy(16,8);
         write('Ano: ');
         readln(rh.ano);
         if verificaAno(rh.ano) then
            begin
               {atualizando o salario}
               if pesquisaHistoricoSalario(histSal,r.matricula,rh.mes,rh.ano)=-1 then
               begin
                    seek(af,posicao);
                    write(af,r);
                    {inserindo um novo registro no histÛrico de sal·rio}
                     seek(HistSal,filesize(HistSal));
                     write(histSal,rh);

               end
               else
               begin
                    textcolor(yellow);
                    gotoxy(13,23);
                    writeln('Alteracao Incorreta! Pressione uma tecla para continuar');
                    readkey;
               end;
            end
            else
            begin
                  textcolor(yellow);
                  gotoxy(16,23);
                  writeln('Ano Incorreto! Pressione uma tecla para continuar');
                  readkey;
            end;

       end else
       begin
         textcolor(yellow);
         gotoxy(16,23);
         writeln('Mes Incorreto! Pressione uma tecla para continuar');
         readkey;
       end;

    end;
     textcolor(white);
     gotoxy(32,20);
     write('Deseja sair S/N ');
     sair:= readkey;
     sair:= upcase(sair);
   until sair='S';
 end;

 {==================================ALTERAR FUNCIONARIO=====================}

 procedure alterarfunc(var AF:Tarq_Func; var AHF:Tarq_Hist_Func; var ad:TArq_Dep);
 var
     r:Treg_func;
     rhf:Treg_hist_func;
     sair:char;
     posicao:integer;
     achou:boolean;
     aux:string[2];
 begin
  repeat
     achou:=true;
     clrscr;
     borda();
     textcolor(white);
     gotoxy(26,2);
     write('Alterar Dados de Funcionario');
     gotoxy(16,5);
     write('Matricula: ');
     readln(r.matricula);
     posicao := pesquisaFunc(af,r.matricula);
     if posicao = -1 then
     begin
       textcolor(yellow);
       gotoxy(13,23);
       writeln('Matricula Inexistente! Pressione uma tecla para continuar');
       readkey;
     end
     else
     begin
      seek(af,posicao);
      read(af,r);
         textcolor(white);
         gotoxy(16,6);
         write('Nome: ');
         readln(r.nome);
       achou:= nome(r.nome);
       if achou then
       begin
       gotoxy(16,7);
         write('Codigo Departamento: ');
         readln(r.codigoDepartamento);

         if pesquisaDep(ad,r.codigoDepartamento) = -1 then
           begin
             textcolor(yellow);
             gotoxy(10,23);
             writeln('Departamento Inexistente! Pressione uma tecla para continuar');
             readkey;
           end
           else
           begin
         rhf.codigoDepartamento := r.codigoDepartamento;
         gotoxy(16,8);
         write('Data de Nascimento (DD/MM/AAAA): ');
         readln(r.DataNascimento);
         achou:=data(r.DataNascimento);
         if achou then
         begin
          gotoxy(16,9);
          write('CPF: ');
          readln(r.cpf);
          achou := valida_cpf(r.cpf);
          if achou then
          begin
          gotoxy(16,10);
          write('Rua: ');
          readln(r.rua);
          gotoxy(16,11);
          write('Bairro: ');
          readln(r.bairro);
          gotoxy(16,12);
          write('Numero: ');
          readln(r.numero);
          achou:=procurarletra(r.numero);
          if achou then
          begin
            gotoxy(16,13);
            write('Complemento: ');
            readln(r.complemento);
            gotoxy(16,14);
            write('Cidade: ');
            readln(r.cidade);
            gotoxy(16,15);
            write('Estado (UF): ');
            readln(r.estado);
            aux:=upcase(r.estado);
            estados(aux,achou);
            if achou then
               begin
                 gotoxy(16,16);
                 write('Email: ');
                 readln(r.email);
                 achou:=validaemail(r.email);
                 if achou then
                 begin

                   gotoxy(16,17);
                   write('Salario: R$');
                   readln(r.salario);
                   if r.salario >= 0 then
                   begin
                     seek(af,filesize(af));
                     write(af,r);
                   end
                   else
                   begin
                     textcolor(yellow);
                     gotoxy(14,23);
                     writeln('Salario Invalido! Pressione uma tecla para continuar');
                     readkey;
                   end; {END DO SALARIO}

                 end
                 else
                 begin
                   textcolor(yellow);
                   gotoxy(16,23);
                   writeln('Email Invalido! Pressione uma tecla para continuar');
                   readkey;
                 end;{END DO EMAIL}

               end
               else
               begin
                 textcolor(yellow);
                 gotoxy(14,23);
                 writeln('Estado Invalido! Pressione uma tecla para continuar');
                 readkey;
               end;{END DO ESTADO DEPOIS DO ELSE}
             end
             else
             begin
               textcolor(yellow);
               gotoxy(15,23);
               writeln('Numero Invalido! Pressione uma tecla para continuar');
               readkey;
             end;{END DO NUMERO}
            end
            else
            begin
              textcolor(yellow);
              gotoxy(16,23);
              writeln('CPF invalido! Pressione uma tecla para continuar');
              readkey;
            end;{END do CPF DEPOIS DO ELSE}
         end
         else
         begin
           textcolor(yellow);
           gotoxy(15,23);
           writeln('Data Invalida! Pressione uma tecla para continuar');
           readkey;
         end;{END da DATA DE NASCIMENTO DEPOIS DO ELSE}
        end;{END VERIFICAR DEPARTAMENTO EXISTENTE}
       end
       else
       begin
           textcolor(yellow);
           gotoxy(15,23);
           writeln('Nome Invalido! Pressione uma tecla para continuar');
           readkey;
       end;{END do NOME }


      {atualizando o funcionario}
       seek(af,posicao);
       write(af,r);
      {inserindo um novo registro no histÛrico de funcionario}
       getdate(ano, mes, dia, diasem);
       rhf.data:=pegardata(dia,mes,ano);
       seek(AHF,filesize(AHF));
       write(AHF,rhf);



     end;{END Verificar Matricula Existente}

     textcolor(white);
     gotoxy(32,20);
     write('Deseja sair S/N ');
     sair:= readkey;
     sair:= upcase(sair);
  until sair='S';
 end;

 {=======================CONSULTAR FUNCIONARIO POR MATRICULA=================}

 procedure consultaFunc(var AF:Tarq_Func);
 var
     r:Treg_func;
     sair:char;
     posicao:integer;
     auxs:string;
     auxr:real;
     auxi:integer;
 begin
   repeat
     clrscr;
     borda();
     textcolor(white);
     gotoxy(26,2);
     write('Alterar Dados de Funcionario');
     gotoxy(16,5);
     write('Matricula: ');
     readln(r.matricula);
     posicao := pesquisaFunc(af,r.matricula);
     if posicao = -1 then
     begin
       textcolor(yellow);
       gotoxy(13,23);
       writeln('Matricula Inexistente! Pressione uma tecla para continuar');
       readkey;
     end
     else
     begin
         seek(af,posicao);
         read(af,r);
         auxs:=r.nome;
         gotoxy(16,7);
         write('Nome: ',upcase(auxs));
         auxi:=r.CodigoDepartamento;
         gotoxy(16,8);
         write('Departamento: ',auxi);
         auxr:=r.salario;
         gotoxy(16,9);
         write('Salario: R$',auxr:0:2);
         auxs:=r.DataNascimento;
         gotoxy(16,10);
         write('Data de Nascimento: ',upcase(auxs));
         auxs:=r.cpf;
         gotoxy(16,11);
         write('CPF: ',upcase(auxs));
         auxs:=r.estado;
         gotoxy(16,12);
         write('Estado: ',upcase(auxs));
         auxs:=r.cidade;
         gotoxy(16,13);
         write('Cidade: ',upcase(auxs));
         auxs:=r.rua;
         gotoxy(16,14);
         write('Rua: ',upcase(auxs));
         auxs:=r.bairro;
         gotoxy(16,15);
         write('Bairro: ',upcase(auxs));
         auxs:=r.numero;
         gotoxy(16,16);
         write('Numero: ',upcase(auxs));
         auxs:=r.complemento;
         gotoxy(16,17);
         write('Complemento: ',upcase(auxs));
         auxs:=r.email;
         gotoxy(16,18);
         write('Email: ',upcase(auxs));


     end;{END Verificar Matricula Existente}
     textcolor(white);
     gotoxy(32,20);
     write('Deseja sair S/N ');
     sair:= readkey;
     sair:= upcase(sair);
   until sair='S';
 end;



{=======================ALTERAR DEPARTAMENTO FUNCIONARIO====================}

 procedure alterardepfunc (var af:Tarq_Func; var ahf:Tarq_Hist_Func; var ad:TArq_Dep);
 var
     r:Treg_func;
     sair:char;
     posicao,posicao2:integer;
     rhf:Treg_hist_func;

 begin
    repeat
     clrscr;
     borda();
     textcolor(white);
     gotoxy(24,2);
     write('Alterar Departamento do Funcionario');
     gotoxy(16,5);
     write('Matricula: ');
     readln(r.matricula);
     posicao := pesquisaFunc(af,r.matricula);
     if posicao = -1 then
     begin
       textcolor(yellow);
       gotoxy(13,23);
       writeln('Matricula Inexistente! Pressione uma tecla para continuar');
       readkey;
     end {END Matricula erro}
     else
      begin
      {lendo arquivo de funcion·rio-------<}
      seek(af,posicao);
      read(af,r);
      {------------------------------------}
      {FALTA LER HISTORICO DE FUNCIONARIO E MANDAR UM PONTEIRO PARA A MATRICULA
      CORRETA DE CADA FUNCIONARIO}
      gotoxy(16,6);
       write('Codigo Departamento: ');
       readln(r.codigodepartamento);
       posicao2:=pesquisaDep (ad,r.codigodepartamento);
       if posicao2 <> -1 then
       begin
          rhf.codigodepartamento := r.codigodepartamento;
         {atualizando o codigo do funcionario}
            seek(af,posicao);
            write(af,r);
        {inserindo um novo registro no histÛrico de funcionario}
           getdate(ano, mes, dia, diasem);
           rhf.data:=pegardata(dia,mes,ano);
           seek(AHF,filesize(AHF));
           write(AHF,rhf);

       end
        else
         begin
          textcolor(yellow);
          gotoxy(12,23);
          writeln('Departamento Inexistente! Pressione uma tecla para continuar');
          readkey;
         end;


      end;

       if (posicao2 <> -1) and (posicao=1) then
       begin
         textcolor(yellow);
         gotoxy(26,23);
         writeln('Codigo Alterado Com Sucesso!!');
       end;
       textcolor(white);
      gotoxy(32,20);
     write('Deseja sair S/N ');
     sair:= readkey;
     sair:= upcase(sair);
   until sair='S';
   end;

{=====================ALTERAR GERENTE DE UM DEPARTAMENTO====================}

 procedure alterargerentedep (var ad:TArq_Dep; var ahd:Tarq_hist_dep);

var  r:Treg_Dep;
     rhd:Treg_hist_dep;
     sair : char;
     posicao: integer;

 begin
   repeat
     clrscr;
     borda();
     textcolor(white);
     gotoxy(24,2);
     writeln('Alterar Gerente de um Departamento');
     gotoxy(16,5);
     write('Codigo do Departamento: ');
     readln(r.codigo);
     posicao:= pesquisaDep(ad,r.codigo);
     if posicao = -1 then
     begin
       textcolor(yellow);
       gotoxy(14,23);
       writeln('Codigo Inexistente! Pressione uma tecla para continuar');
       readkey;
     end
     else
     begin
     {Abrindo arquivo do departamento}
      seek(ad,posicao);
      read(ad,r) ;
     {------------------------------}
      gotoxy(16,6);
       write('Codigo Gerente: ');
       readln(r.codigogerente);
       rhd.codigogerente := r.codigogerente;
      {atualizando o codigo do gerente}
       seek(ad,posicao);
       write(ad,r);
      {inserindo um novo registro no histÛrico de departamento}
       seek(ahd,filesize(ahd));
       write(ahd,rhd);
       textcolor(yellow);
       gotoxy(21,23);
       writeln('Codigo Gerente Alterado Com Sucesso!!');
     end;
      textcolor(white);
      gotoxy(32,20);
     write('Deseja sair S/N ');
     sair:= readkey;
     sair:= upcase(sair);
   until sair='S';
   end;


{============================GERAR FOLHA PAGAMENTO==========================}

 procedure folhapagamento (var af:Tarq_func);

 var
     r:Treg_func;
     sair:char;
     posicao:integer;
     auxn:string;
     auxs:real;
     auxm:integer;
 begin
   repeat
     clrscr;
     borda();
     textcolor(white);
     gotoxy(32,2);
     write('Folha de Pagamento');
     gotoxy(16,5);
     write('Matricula: ');
     readln(r.matricula);
     posicao := pesquisaFunc(af,r.matricula);
     if posicao = -1 then
     begin
       textcolor(yellow);
       gotoxy(13,23);
       writeln('Matricula Inexistente! Pressione uma tecla para continuar');
       readkey;
     end
     else
     begin
     seek(af,posicao);
         read(af,r);
         auxm:=r.matricula;
         gotoxy(16,7);
         write('Matricula: ',auxm);
         auxn:=r.nome;
         gotoxy(16,8);
         write('Nome: ',upcase(auxn));
         auxs:=r.salario;
         gotoxy(16,9);
         write('Salario: R$',auxs:0:2);
      end;
     textcolor(white);
     gotoxy(32,20);
     write('Deseja sair S/N ');
     sair:= readkey;
     sair:= upcase(sair);
   until sair='S';
 end;

 {====================== GERENTES DE UM DEPARTAMENTO =======================}

 procedure gerenteDeDepartamento ();
 begin
      clrscr;
      borda();

      textcolor(yellow);
      gotoxy(17,12);
      writeln('DADOS INSUFICIENTES PARA GERAR ESTE PROCEDIMENTO');
      gotoxy(28,13);
      write('ENTER PARA VOLTAR AO MENU');
      readkey;
 end;

 {=================RELATORIO DE FUNCIONARIO POR DEPARTAMENTO================}
 procedure relatoriofunc(var ad:TArq_Dep; var af:TArq_Func);
 var r:TReg_Dep;
     posicao:integer;
     sair:char;
 begin
    repeat
      clrscr;
      borda();
      textcolor(white);
      gotoxy(29,2);
      write('Relatorio de Funcionarios');
      gotoxy(16,5);
      write('Departamento: ');
      readln(r.codigo);
      if pesquisaDep(ad, r.codigo) = -1 then
          begin
          textcolor(yellow);
          gotoxy(14,23);
          writeln('Codigo Inexistente! Pressione uma tecla para continuar');
          readkey;
          end
       else
           begin
                posicao:= pesquisaDep(ad, r.codigo);
                seek(ad, posicao);
                read(ad,r);
                gotoxy(16,7);
                writeln('Nome do Departamento: ',r.nome);
                textcolor(yellow);
                gotoxy(16,9);
                writeln('   Matricula           Nome           Salario');
                textcolor(white);
                gotoxy(33,9);
                writeln('|');
                gotoxy(49,9);
                writeln('|');
                pesquisaRelatorio(af,r.codigo);
                readkey;
           end;

     textcolor(white);
     gotoxy(32,20);
     write('Deseja sair S/N ');
     sair:= readkey;
     sair:= upcase(sair);
   until sair='S';
 end;

 {======================HISTORICO DE SALARIO EM UM PERIODO==================}
 procedure salarioperiodo(var AF:Tarq_Func;var HistSal:TArq_Hist_Sal);
 var r:Treg_func;
     posicao:integer;
     rh : TReg_Hist_Sal;
     sair:char;
     mesi,mesf,anoi,anof:integer;

 begin
   repeat
     seek(histsal,0);
     read(histsal,rh);
     clrscr;
     borda();
     textcolor(white);
     gotoxy(25,2);
     write('Historico de Salario por Periodo');
     gotoxy(16,5);
     write('Matricula: ');
     readln(r.matricula);
     posicao := pesquisaFunc(af,r.matricula);
     if posicao = -1 then
     begin
       textcolor(yellow);
       gotoxy(13,23);
       writeln('Matricula Inexistente! Pressione uma tecla para continuar');
       readkey;
     end
     else
     begin
          gotoxy(20,7);
          write('Mes Inicial: ');
          readln(mesi);
          if not verificaMes(mesi) then
             begin
              textcolor(yellow);
              gotoxy(16,23);
              writeln('Mes Incorreto! Pressione uma tecla para continuar');
              readkey;
             end
             else
             begin
              gotoxy(20,8);
              write('Ano Inicial: ');
              readln(anoi);
              if not verificaAno(anoi) then
               begin
                 textcolor(yellow);
                 gotoxy(16,23);
                 writeln('Ano Incorreto! Pressione uma tecla para continuar');
                 readkey;
               end
               else
               begin
                 gotoxy(45,7);
                 write('Mes Final: ');
                 readln(mesf);
                 if not verificaMes(mesf) then
                  begin
                   textcolor(yellow);
                   gotoxy(16,23);
                   writeln('Mes Incorreto! Pressione uma tecla para continuar');
                   readkey;
                 end
                 else
                 begin
                  gotoxy(45,8);
                  write('Ano Final: ');
                  readln(anof);
                  if not verificaAno(anof) then
                   begin
                    textcolor(yellow);
                    gotoxy(16,23);
                    writeln('Ano Incorreto! Pressione uma tecla para continuar');
                    readkey;
                   end
                   else
                   begin
                    textcolor(yellow);
                    gotoxy(24,10);
                    writeln('Mes / Ano               Salario');
                    textcolor(white);
                    PesSalPeriodo(HistSal,mesi,mesf,anoi,anof,r.matricula);


                   end;{END ANO FINAL}


                 end; {END MES FINAL}


               end;{END ANO INICIAL}


          end;{END MES INICIAL}


     end;


     textcolor(white);
     gotoxy(32,20);
     write('Deseja sair S/N ');
     sair:= readkey;
     sair:= upcase(sair);
   until sair='S';
 end;

 {==============================INICIO DO PROGRAMA==========================}

begin
{===============================ABRINDO ARQUIVOS ===========================}
  assign(ArqDep,'departamento.dat');
  {$I-}
  reset(ArqDep);
  {$I+}
  if IOResult <> 0 then
    rewrite(ArqDep);

  assign(ArqFunc,'funcionario.dat');
  {$I-}
  reset(ArqFunc);
  {$I+}
  if IOResult <>0 then
    rewrite(ArqFunc);

  assign(ArqHistSal,'HistoricoSalario.dat');
  {$I-}
  reset(ArqHistSal);
  {$I+}
  if IOResult <>0 then
    rewrite(ArqHistSal);

  assign(ArqHistFunc,'HistoricoFuncionario.dat');
  {$I-}
  reset(ArqHistFunc);
  {$I+}
  if IOResult <> 0 then
    rewrite(ArqHistFunc);

  assign(ArqHistDep,'HistoricoDepartamento.dat');
  {$I-}
  reset(ArqHistDep);
  {$I+}
  if IOResult <> 0 then
    rewrite(ArqHistDep);

 repeat
 {Window decorativo ----------------------------------------------------<}
    textbackground(blue);
    window(1,1,80,25);
    clrscr;
    textbackground(black);
    window(2,2,79,24);
    clrscr;
    textcolor(white);
 {Window decorativo ----------------------------------------------------<}

 {-------------------------Escrevendo o menu na tela----------------------}
	clrscr;
	x:=1;
    cor:=14;
    borda();
    textcolor(yellow);
    gotoxy(20,23);
    writeln('Autores: Mateus Ferreira , Edgar Ferreira');
    gotoxy(37,2);
    writeln(' MENU ');

    {Data do menu}
    textcolor(white);
    getdate(ano, mes, dia, diasem);
    data2:=pegardata(dia,mes,ano);
    gotoxy(69,2);
    writeln(data2);



	repeat
 	gotoxy(19,5);
	if x=1 then
		mudacor;
	write('Cadastro de Departamento                   ');
	voltacor;
	gotoxy(19,6);
	if x=2 then
		mudacor;
	write('Cadastro de Funcionario                    ');
	voltacor;
	gotoxy(19,7);
	if x=3 then
		mudacor;
	write('Alterar Funcionario                        ');
	voltacor;
	gotoxy(19,8);
	if x=4 then
		mudacor;
	write('Alterar Departamento de Funcionario        ');
	voltacor;
	gotoxy(19,9);
	if x=5 then
		mudacor;
	write('Alterar o Gerente um Departamento          ');
	voltacor;
	gotoxy(19,10);
	if x=6 then
		mudacor;
	write('Consultar Funcionario por Matricula        ');
	voltacor;
	gotoxy(19,11);
	if x=7 then
		mudacor;
	write('Gerar Folha Pagamento                      ');
	voltacor;
	gotoxy(19,12);
	if x=8 then
		mudacor;
	writeln('Alterar o Salario de um Funcionario        ');
	voltacor;
	gotoxy(19,13);
	if x=9 then
		mudacor;
	write('Relatorio de Funcionarios por Departamento ');
	voltacor;
	gotoxy(19,14);
	if x=10 then
		mudacor;
	write('Historico de Salario por Periodo           ');
	voltacor;
	gotoxy(19,15);
	if x=11 then
		mudacor;
	write('Gerente de um Departamento                 ');
	voltacor;
	gotoxy(37,16);
	if x=12 then
		mudarcorsair(cor);
       textcolor(cor);
	write('  Sair  ');
	voltarcorsair(cor);

    {seta}

    y:=16;
	textcolor(white);
	gotoxy(y,4+x);
	writeln(chr(62),chr(62));
	voltacor;
	
    {Modificando a seta }

	tecla:=readkey;
	tecla:=upcase(tecla);
	case tecla of
		#80 :begin gotoxy(y,4+x); writeln('  '); x:=x+1; end;
		#72 :begin gotoxy(y,4+x); writeln('  '); x:=x-1; end;
	end; 		
	if x=0 then
        x:=12
	else
	if x=13 then
		x:=1;

	until tecla=#13;
    op:= x;
{case apos menu ------------------------------------------------------------<}
    case op of
      1: cadastroDepartamento(ArqDep);
      2: cadastroFuncionario(ArqFunc,ArqDep);
      3: alterarFunc(ArqFunc,ArqHistFunc,ArqDep);
      4: alterardepfunc(ArqFunc,ArqHistFunc,ArqDep);
      5: alterargerentedep(ArqDep,ArqHistDep);
      6: consultaFunc(ArqFunc);
      7: folhapagamento(ArqFunc);
      8: alterarSalario(ArqFunc,ArqHistSal);
      9: relatoriofunc(ArqDep,ArqFunc);
      10: salarioperiodo(ArqFunc,ArqHistSal);
      11: gerenteDeDepartamento();
      12:;
    end;
 until op = 12;
{===================================FECHANDO ARQUIVOS=========================}
  close(ArqDep);
  close(ArqFunc);
  close(ArqHistSal);
  close(ArqHistFunc);
  close(ArqHistDep);
end.

