<?php

	$quantidade = $_GET["quantidade"];


	$dados[0]="12|AAA|2400|2005-08-15|Global|3|2\n";
	$dados[1]="11|BBB|2200|2005-08-14|Global|3|2\n";
	$dados[2]="1|david|1400|2005-07-12|Global|1|2\n";
	$dados[3]="2|daniel|1300|2005-07-11|Global|1|2\n";
	$dados[4]="3|junior|1200|2005-07-10|Global|1|2\n";
	$dados[5]="4|alex_r|1111|2005-07-09|Global|1|2\n";
	$dados[6]="5|vader|1110|2005-07-08|Global|1|2\n";
	$dados[7]="6|killocan|1100|2005-07-07|Global|1|2\n";
	$dados[8]="7|alele|1000|2005-07-06|Global|1|2\n";
	$dados[9]="8|dgm|999|2005-07-05|Global|1|2\n";
	$dados[10]="9|f-z|99|2005-07-04|Global|1|2\n";
	$dados[11]="10|mailto|9|2005-07-03|Global|1|2\n";


	for ($i=0;$i<$quantidade;$i++){

		echo $dados[$i];

	}

?>
