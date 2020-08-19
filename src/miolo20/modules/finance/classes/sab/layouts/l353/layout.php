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
 * @author Leovan Tavares da Silva [leovan] [leovan@solis.coop.br]
 *
 * $version: $Id$
 *
 * \b Maintainers \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Arthur Lehdermann [arthur@solis.coop.br]
 * Daniel Afonso Heisler [daniel@solis.coop.br]
 * Jamiel Spezia [jamiel@solis.coop.br]
 * Leovan Tavares da Silva [leovan@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 * 
 * @since
 * Class created on 14/06/2006
 *
 **/
 
/*
 * TODO: Make a decent header
 */ 
class sabStruct extends sabCore
{
   /*
    * By default called on new instance of this object
    * @params: No parameters needed
    * @return: Nothing, set the default information for that object
    */
    public function __construct()
    {
        parent::__construct('353');
        $this->setBankCode('353');
        $this->setBankDV('0');
        $this->setInvoiceNumber('1234567890');
        
        //Define wallet
        $this->setInvoiceWallet('8');

        if ( strlen($this->getInvoiceProcessDate()) == 0 )
        {
            $this->setInvoiceProcessDate(date('d/m/Y'));
        }
        if ( strlen($this->getInvoiceDate()) == 0 )
        {
            $this->setInvoiceDate(date('d/m/Y'));
        }
        $this->setNumberOfBodies(3);
        $this->setHeaderInfo(1, 'TEXT', 'RECIBO DO SACADO');
        $this->setHeaderInfo(2, 'TEXT', 'FICHA DE CAIXA');
        $this->setHeaderInfo(3, 'DIGITABLE NUMBER');

        if ( strlen($this->getPaymentPlaceDescription()) == 0 )
        {
            $this->setPaymentPlaceDescription(_('Pague preferencialmente nas ag�ncias do SANTANDER'));
        }
        $vars = get_object_vars($this);
    }

   /*
    * Set the invoice number (parent abstract function)
    * TODO: MAKE THIS FUNCTION WORK ON CORRECT PARAMETERS
    * @param: No parameters needed
    * @return: No return, just change the sab object property our number 
    */
    public function setInvoiceNumber($invoiceNumber)
    {
        $this->invoiceNumber = $invoiceNumber;
        return true;
    }

   /*
    * Set the invoice our number (parent abstract function)
    * TODO: MAKE THIS FUNCTION WORK ON CORRECT PARAMETERS
    * @param: $invoiceOurNumber (The our number)
    * @return: No return, just change the sab object property our number 
    */
    public function setInvoiceOurNumber($invoiceOurNumber)
    {
        $this->invoiceOurNumber = $invoiceOurNumber;
        return true;
    }


   /*
    * Set the invoice our number DV (parent abstract function)
    * TODO: MAKE THIS FUNCTION WORK ON CORRECT PARAMETERS
    * @param: $invoiceOurNumberDV (The DV for our number)
    * @return: No return, just change the sab object property our number DV
    */
    public function setInvoiceOurNumberDV($invoiceOurNumberDV = null)
    {
        if (is_null($invoiceOurNumberDV))
        {
            $this->invoiceOurNumberDV = fields::modulo10($this->getInvoiceOurNumber());
        }
        else
        {
            $this->invoiceOurNumberDV = $invoiceOurNumberDV;
        }
        return true;
    }


   /*
    * Set the transferor code (parent abstract function)
    * TODO: MAKE THIS FUNCTION WORK ON CORRECT PARAMETERS
    * @param: No parameters needed
    * @return: No return, just change the sab object property our number 
    */
    public function setTransferorCode($transferorCode)
    {
        $this->transferorCode = $transferorCode;
        return true;
    }

    /**
    * Get the dv1 and dv2 number (parent abstract function)
    * @return: $dv1dv2
    **/
    public function getDV1DV2($num, $dv1, $factor = 2, $factorMax = 7)
    {
        $dvS = true;

        while($dvS)
        {
            $numDV1  = $num.''.$dv1;
            $totalX  = 0;
            $value   = array();
            $factor_ = $factor;
            for ( $x = strlen($numDV1); $x > 0; $x-- )
            {
                $pos       = substr($numDV1, $x-1, 1);
                $value[$x] = $pos*$factor;
                if ( $factor == $factorMax )
                {
                    $factor = $factor_;
                }
                else
                {
                    $factor++;
                }
            }
            $totalX = array_sum($value);
            $mod    = $totalX % 11;

            if($mod == 1)
            {
                if($dv1 == 9)
                {
                    $dv1 = 0;
                }
                elseif($dv1 < 9)
                {
                    $dv1 ++;
                }
            }
            else
            {
                $dvS = false; 
            }
        }
        if ( $mod > 1 )
        {
            return $dv1.''.( 11 - $mod );
        }
        else
        {
            return $dv1.'0';
        }
    }
    
    /*
    * Get the invoice value
    * @params: No parameters needed
    * @return: (float) The invoice value if that exists
    */
    public function getFormattedInvoiceValue()
    {
        return number_format($this->getInvoiceValue(), 2, ',', '');
    }

}
?>
