<?php
    //ini_set('display_errors', true);
    $con = new PDO("pgsql:host=localhost;dbname=sagu", "postgres", "postgres");

    if (!$con) {
        echo 'n�o conectou';
    }


    $sql = "SELECT dataatendimento FROM aps.fastmedic_detalhamentosdiarios ORDER BY dataatendimento DESC LIMIT 1;";
    $query1 = $con->query($sql);
    $dataUltimaAtualizacao = null;
    while ($row = $query1->fetch(PDO::FETCH_OBJ)) {
        $dataUltimaAtualizacao = $row->dataatendimento;
    }

    if ($dataUltimaAtualizacao == null) {
        $dataInicial = '2019-08-01';
        $dataFinal = '2019-08-01';

    } else {

        $dataInicial = date('Y-m-d', strtotime($dataUltimaAtualizacao. ' + 1 days'));
        $dataFinal =  date('Y-m-d', strtotime($dataUltimaAtualizacao. ' + 7 days'));
    }


    $curl = curl_init();
    curl_setopt_array($curl, array(
        CURLOPT_URL => "http://services.sms.fortaleza.ce.gov.br/ap/esp/detalhamento-diario",
        CURLOPT_RETURNTRANSFER => true,
        CURLOPT_ENCODING => "",
        CURLOPT_MAXREDIRS => 10,
        CURLOPT_TIMEOUT => 600,
        CURLOPT_FOLLOWLOCATION => false,
        CURLOPT_HTTP_VERSION => CURL_HTTP_VERSION_1_1,
        CURLOPT_CUSTOMREQUEST => "POST",
        CURLOPT_POSTFIELDS =>"{\n\t\"dataInicial\":\"{$dataInicial}\",\n\t\"dataFinal\": \"{$dataFinal}\"\n}",
        CURLOPT_HTTPHEADER => array(
            "Content-Type: application/json",
            "X-Requested-With: XMLHttpRequest",
            "X-Auth-Token: qXmSdLxYRsAUqfeKqVrNhxsjJDtSpjSD"
        ),
    ));


    $response = curl_exec($curl);
    $err = curl_error($curl);

    curl_close($curl);

    if ($err) {
        echo "cURL Error #:" . $err;
    } else {

        $jsonDecodificado = json_decode($response, true);

        $dataRegistro = date('Y-m-d');
        foreach($jsonDecodificado as $value) {

            $cpf = mask($value['profissional_cpf'], '###.###.###-##');
            $sql = "
                    SELECT DISTINCT P.residenteid
                    FROM aps.residente P
                    INNER JOIN basPhysicalPerson PP
                            ON P.personId = PP.personId
                    INNER JOIN basDocument CPF
                            ON PP.personId = CPF.personId
                    WHERE CPF.content = '" . $cpf . "' LIMIT 1;
            ";
            $query1 = $con->query($sql);
            while ($row = $query1->fetch(PDO::FETCH_OBJ)) {

                $sqlInsert = "INSERT INTO aps.fastmedic_detalhamentosdiarios (dataregistro, aluno, dataatendimento, horainicial,  horafinal, tempototal, quantidade, tempomedio) 
                            VALUES ('". $dataRegistro ."', '". $row->residenteid ."', '". $value['data'] ."', '". $value['hora_incial'] ."', '". $value['hora_final'] ."', '". $value['tempo_total'] ."', '". $value['quantidade'] ."', '". $value['tempo_medio'] ."')";

                echo $sqlInsert . '<br>';
                $con->exec($sqlInsert);
            }
        }
    }



function mask($val, $mask)
{
    $maskared = '';
    $k = 0;
    for($i = 0; $i<=strlen($mask)-1; $i++)
    {
        if($mask[$i] == '#')
        {
            if(isset($val[$k]))
                $maskared .= $val[$k++];
        }
        else
        {
            if(isset($mask[$i]))
                $maskared .= $mask[$i];
        }
    }
    return $maskared;
}

?>