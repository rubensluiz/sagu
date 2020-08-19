<?php
/**
 * <--- Copyright 2005-2010 de Solis - Cooperativa de Solu��es Livres Ltda.
 *
 * Este arquivo � parte do programa Sagu.
 *
 * O Sagu � um software livre; voc� pode redistribu�-lo e/ou modific�-lo
 * dentro dos termos da Licen�a P�blica Geral GNU como publicada pela Funda��o
 * do Software Livre (FSF); na vers�o 2 da Licen�a.
 *
 * Este programa � distribu�do na esperan�a que possa ser �til, mas SEM
 * NENHUMA GARANTIA; sem uma garantia impl�cita de ADEQUA��O a qualquer MERCADO
 * ou APLICA��O EM PARTICULAR. Veja a Licen�a P�blica Geral GNU/GPL em
 * portugu�s para maiores detalhes.
 *
 * Voc� deve ter recebido uma c�pia da Licen�a P�blica Geral GNU, sob o t�tulo
 * "LICENCA.txt", junto com este programa, se n�o, acesse o Portal do Software
 * P�blico Brasileiro no endere�o www.softwarepublico.gov.br ou escreva para a
 * Funda��o do Software Livre (FSF) Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA --->
 *
 *
 * This class Make a decent header
 *
 * @author Arthur Lehdermann [arthur] [arthur@solis.coop.br]
 *
 * $version: $Id$
 *
 * \b Maintainers \n
 * Arthur Lehdermann [arthur@solis.coop.br]
 *
 * @since
 * Class created on 26/08/2010
 *
 **/

/*
 * TODO: Make a decent header
 */
class sabStructOnline extends sabCore
{
    public $accNumber;
    public $aditional = array();
    public $aditionalValue = array();
    public $agNumber;
    public $bank;
    public $cip;
    public $description = array();
    public $directory;
    public $draweeAddress;
    public $draweeCity;
    public $draweeCpf;
    public $draweeName;
    public $draweeUf;
    public $draweeZipCode;
    public $emissionDate;
    public $instructions = array();
    public $link;
    public $maturityDate;
    public $numDoc;
    public $orderId;
    public $ourNumber;
    public $price = array();
    public $processingDate;
    public $quantity = array();
    public $requestNumber;
    public $shopId;
    public $shoppingId;
    public $signature;
    public $transferor;
    public $unit = array();
    public $url;
    public $valueDocumentFormated;
    public $wallet;

    /*
     * By default called on new instance of this object
     * @params: No parameters needed
     * @return: Nothing, set the default information for that object
     */
    public function __construct()
    {
        parent::__construct('237');
    }

    /**
     * Id da ordem
     * @param: $orderId - Id of the order
     * @return: Return true
     */
    public function setOrderId($orderId)
    {
        $this->orderId = $orderId;

        return true;
    }
    public function getOrderId()
    {
        return $this->orderId;
    }

    /**
     * Adiciona descritivo, quantidade, unidade e valor
     * @param $description
     * @param $quantity
     * @param $unit
     * @param $value
     */
    public function addOrderDescriptionProduct($description, $quantity, $unit, $price)
    {
        $this->description = $description;
        $this->quantity = $quantity;
        $this->unit = $unit;
        $this->price = $price;

        return true;
    }
    public function getOrderDescriptionProductDescription($key)
    {
        return $this->description[$key];
    }
    public function getOrderDescriptionProductQuantity($key)
    {
        return $this->quantity[$key];
    }
    public function getOrderDescriptionProductUnit($key)
    {
        return $this->unit[$key];
    }
    public function getOrderDescriptionProductValue($key)
    {
        return $this->value[$key];
    }

    /**
     * Adicional e valor adicional
     * @param $aditional
     * @param $aditionalValue
     */
    public function addOrderDescriptionAditional($aditional, $aditionalValue)
    {
        $this->aditional = $aditional;
        $this->aditionalValue = $aditionalValue;

        return true;
    }
    /**
     * Recebe por par�metro a chave do adicional desejado
     * Ex.: getOrderDescriptionAditional(1); - retorna o valor de $aditional[1]
     * @param $key - chave do adicional
     * @return $this->aditional[$key] - o adicional desejado
     */
    public function getOrderDescriptionAditional($key)
    {
        return $this->aditional[$key];
    }
    /**
     * Recebe por par�metro a chave do valor adicional desejado
     * Ex.: getOrderDescriptionAditionalValue(1); - retorna o valor de $aditionalValue[1]
     * @param $key - chave do valor adicional
     * @return $this->aditionalValue[$key] - o valor adicional desejado
     */
    public function getOrderDescriptionAditionalValue($key)
    {
        return $this->aditionalValue[$key];
    }

    /**
     * Cedente
     * @param: $transferor
     * @return: Return true
     */
    public function setTransferor($transferor)
    {
        $this->transferor = $transferor;

        return true;
    }
    public function getTransferor()
    {
        return $this->transferor;
    }

    /**
     * Banco
     * @param: $bank
     * @return: Return true
     */
    public function setBank($bank)
    {
        $this->bank = $bank;

        return true;
    }
    public function getBank()
    {
        return $this->bank;
    }

    /**
     * N�mero da Ag�ncia
     * @param: $agNumber
     * @return: Return true
     */
    public function setAgNumber($agNumber)
    {
        $this->agNumber = $agNumber;

        return true;
    }
    public function getAgNumber()
    {
        return $this->agNumber;
    }

    /**
     * N�mero da Conta
     * @param: $accNumber
     * @return: Return true
     */
    public function setAccNumber($accNumber)
    {
        $this->accNumber = $accNumber;

        return true;
    }
    public function getAccNumber()
    {
        return $this->accNumber;
    }

    /**
     * Assinatura
     * @param: $signature
     * @return: Return true
     */
    public function setSignature($signature)
    {
        $this->signature = $signature;

        return true;
    }
    public function getSignature()
    {
        return $this->signature;
    }

    /**
     * Data de Emiss�o
     * @param: $emissionDate
     * @return: Return true
     */
    public function setEmissionDate($emissionDate)
    {
        $this->emissionDate = $emissionDate;

        return true;
    }
    public function getEmissionDate()
    {
        return $this->emissionDate;
    }

    /**
     * Data de Processamento
     * @param: $ProcessingDate
     * @return: Return true
     */
    public function setProcessingDate($processingDate)
    {
        $this->processingDate = $processingDate;

        return true;
    }
    public function getProcessingDate()
    {
        return $this->processingDate;
    }

    /**
     * Data de Vencimento
     * @param: $maturityDate
     * @return: Return true
     */
    public function setMaturityDate($maturityDate)
    {
        $this->maturityDate = $maturityDate;

        return true;
    }
    public function getMaturityDate()
    {
        return $this->maturityDate;
    }

    /**
     * Nome do Sacado
     * @param: $draweeName
     * @return: Return true
     */
    public function setDraweeName($draweeName)
    {
        $this->draweeName = $draweeName;

        return true;
    }
    public function getDraweeName()
    {
        return $this->draweeName;
    }

    /**
     * Endere�o do Sacado
     * @param: $draweeAddress
     * @return: Return true
     */
    public function setDraweeAddress($draweeAddress)
    {
        $this->draweeAddress = $draweeAddress;

        return true;
    }
    public function getDraweeAddress()
    {
        return $this->draweeAddress;
    }

    /**
     * Cidade do Sacado
     * @param: $draweeCity
     * @return: Return true
     */
    public function setDraweeCity($draweeCity)
    {
        $this->draweeCity = $draweeCity;

        return true;
    }
    public function getDraweeCity()
    {
        return $this->draweeCity;
    }

    /**
     * Uf do Sacado
     * @param: $draweeUf
     * @return: Return true
     */
    public function setDraweeUf($draweeUf)
    {
        $this->draweeUf = $draweeUf;

        return true;
    }
    public function getDraweeUf()
    {
        return $this->draweeUf;
    }

    /**
     * Cep do Sacado
     * @param: $draweeZipCode
     * @return: Return true
     */
    public function setDraweeZipCode($draweeZipCode)
    {
        $this->draweeZipCode = $draweeZipCode;

        return true;
    }
    public function getDraweeZipCode()
    {
        return $this->draweeZipCode;
    }

    /**
     * Cpf do Sacado
     * @param: $draweeCpf
     * @return: Return true
     */
    public function setDraweeCpf($draweeCpf)
    {
        $this->draweeCpf = $draweeCpf;

        return true;
    }
    public function getDraweeCpf()
    {
        return $this->draweeCpf;
    }

    /**
     * N�mero do Pedido
     * @param: $requestNumber
     * @return: Return true
     */
    public function setRequestNumber($requestNumber)
    {
        $this->requestNumber = $requestNumber;

        return true;
    }
    public function getRequestNumber()
    {
        return $this->requestNumber;
    }

    /**
     * Valor Do Documento Formatado
     * @param $valorDoDocumentoFormatado
     * @return Return true
     */
    public function setValueDocumentFormated($valueDocumentFormated)
    {
        $this->valueDocumentFormated = $valueDocumentFormated;

        return true;
    }
    public function getValueDocumentFormated()
    {
        return $this->valueDocumentFormated;
    }

    /**
     * C�digo da Loja
     * @param: $shoppingId
     * @return: Return true
     */
    public function setShoppingId($shoppingId)
    {
        $this->shoppingId = $shoppingId;

        return true;
    }
    public function getShoppingId()
    {
        return $this->shoppingId;
    }

    /**
     * N�mero do Documento
     * @param: $numDoc
     * @return: Return true
     */
    public function setnumDoc($numDoc)
    {
        $this->numDoc = $numDoc;

        return true;
    }
    public function getnumDoc()
    {
        return $this->numDoc;
    }

    /**
     * Carteira
     * @param: $wallet
     * @return: Return true
     */
    public function setwallet($wallet)
    {
        $this->wallet = $wallet;

        return true;
    }
    public function getWallet()
    {
        return $this->wallet;
    }

    /**
     * Ano Nosso N�mero
     * @param: $ourNumber
     * @return: Return true
     */
    public function setOurNumber($ourNumber)
    {
        $this->ourNumber = $ourNumber;

        return true;
    }
    public function getOurNumber()
    {
        return $this->ourNumber;
    }

    /**
     * Cip
     * @param: $cip
     * @return: Return true
     */
    public function setCip($cip)
    {
        $this->cip = $cip;

        return true;
    }
    public function getCip()
    {
        return $this->cip;
    }

    /**
     * ID da Loja
     * @param: $shopId
     * @return: Return true
     */
    public function setShopId($shopId)
    {
        $this->shopId = $shopId;

        return true;
    }
    public function getShopId()
    {
        return $this->shopId;
    }

    /**
     * Instru��es(de 1 a 12) - Linhas de instru��es de 1 � 12
     * @param: (array) $instructions
     * @return: Return true
     */
    public function setInstructions($instructions)
    {
        $this->instructions = $instructions;

        return true;
    }
    public function getInstructions($key)
    {
        return $this->instructions[$key];
    }

    /**
     * Link do M.U.P.
     * @param: $url
     * @return: Return true
     */
    public function setUrl($url)
    {
        $this->url = $url;

        return true;
    }
    public function getUrl()
    {
        return $this->url;
    }

    /**
     * Define o diret�rio onde ser� salvo o arquivo
     * @param $directory - path
     */
    public function setUploadPath($directory)
    {
        $this->directory = $directory;
    }

    //N�o usadas mas necess�rias para o funcionamento:
    public function setInvoiceOurNumber($ourNumber)
    {

    }
    public function setInvoiceOurNumberDV($ourNumberDV = null)
    {

    }
    public function setInvoiceNumber($invoiceNumber)
    {

    }
    public function setTransferorCode($transferorCode)
    {

    }

    /**
     * Retorna o link para a gera��o do boleto
     */
    public function getLink()
    {
        return $this->link;
    }

    public function generateLink()
    {
        // Grava o arquivo
        $saveFile = $this->saveFile();
        if ( $saveFile )
        {
            $this->link = str_ireplace("ORDER_ID", $this->orderId, $this->getUrl());
            $return = true;
        }
        else
        {
            $return = false;
        }
        return $return;
    }

    private function saveFile()
    {
        //Gera o arquivo com os dados
        $open = fopen($this->directory."/".$this->orderId.".txt","w");

        if ( $open )
        {
            $break = chr(13);
            $write = fwrite($open,"<BEGIN_ORDER_DESCRIPTION>".$break."<orderid>=(".$this->orderId.")".$break);

            for ( $k=0; $k < count($this->description); $k++ )
            {
                if ( strlen($this->description[$k]) > 0 )
                {
                    $write = fwrite($open,"<descritivo>=(".$this->description[0].")".$break);
                    $write = fwrite($open,"<quantidade>=(".$this->quantity[0].")".$break);
                    $write = fwrite($open,"<unidade>=(".$this->unit[0].")".$break);
                    $write = fwrite($open,"<valor>=(".$this->price[0].")".$break);
                }
            }

            for ( $k=0; $k < count($this->aditional); $k++ )
            {
                if ( strlen($this->aditional[$k]) > 0 )
                {
                    $write = fwrite($open,"<adicional>=(".$this->aditional[0].")".$break);
                    $write = fwrite($open,"<valorAdicional>=(".$this->aditionalValue[0].")".$break);
                }
            }

            $write = fwrite($open,"<END_ORDER_DESCRIPTION>".$break);
            $write = fwrite($open,"<BEGIN_BOLETO_DESCRIPTION><CEDENTE>=(".$this->transferor.")".$break);
            $write = fwrite($open,"<BANCO>=(".$this->bank.")".$break);
            $write = fwrite($open,"<NUMEROAGENCIA>=(".$this->agNumber.")".$break);
            $write = fwrite($open,"<NUMEROCONTA>=(".$this->accNumber.")".$break);
            $write = fwrite($open,"<ASSINATURA>=(".$this->signature.")".$break);
            $write = fwrite($open,"<DATAEMISSAO>=(".$this->emissionDate.")".$break);
            $write = fwrite($open,"<DATAPROCESSAMENTO>=(".$this->processingDate.")".$break);
            $write = fwrite($open,"<DATAVENCIMENTO>=(".$this->maturityDate.")".$break);
            $write = fwrite($open,"<NOMESACADO>=(".$this->draweeName.")".$break);
            $write = fwrite($open,"<ENDERECOSACADO>=(".$this->draweeAddress.")".$break);
            $write = fwrite($open,"<CIDADESACADO>=(".$this->draweeCity.")".$break);
            $write = fwrite($open,"<UFSACADO>=(".$this->draweeUf.")".$break);
            $write = fwrite($open,"<CEPSACADO>=(".$this->draweeZipCode.")".$break);
            $write = fwrite($open,"<CPFSACADO>=(".$this->draweeCpf.")".$break);
            $write = fwrite($open,"<NUMEROPEDIDO>=(".$this->numDoc.")".$break);
            $write = fwrite($open,"<VALORDOCUMENTOFORMATADO>=(".$this->valueDocumentFormated.")".$break);
            $write = fwrite($open,"<SHOPPINGID>=(".$this->shoppingId.")".$break);
            $write = fwrite($open,"<NUMDOC>=(".$this->numDoc.")".$break);
            $write = fwrite($open,"<CARTEIRA>=(".$this->wallet.")".$break);
            $write = fwrite($open,"<CIP>=(".$this->cip.")".$break);

            for ( $k=0; $k<12; $k++ )
            {
                $i = $k+1;
                if ( strlen($this->instructions[$k]) > 0)
                {
                    $write = fwrite($open,"<INSTRUCAO".$i.">=(".$this->instructions[$k].")".$break);
                }
            }

            $write = fwrite($open,"<END_BOLETO_DESCRIPTION>");
        }
        else
        {
            // N�o foi poss�vel abrir/criar o arquivo
            $return =  false;
        }

        if ( $write )
        {
            $return = fclose($open);
        }
        else
        {
            // N�o foi poss�vel gravar no arquivo
            $return = false;
        }

        return $return;
    }
}
?>