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
 * This class Fields Struct
 *
 * @author Equipe Sagu [sagu@solis.com.br]
 *
 * $version: $Id$
 *
 * \b Maintainers \n
 * Equipe Sagu [sagu@solis.com.br]
 * 
 * @since
 * Class created on 08/01/2013
 *
 **/
 
class fieldsStruct extends fields
{
    
    protected $mod;
    
   /*
    * Function to construct that object, by default calls the parent function to set default 
    * values to some variables
    * @param: $sabStruct (sabStruct object)
    * @return: Nothing. 
    */
    public function __construct(sabStruct $sabStruct)
    {
        parent::__construct($sabStruct);
    }

    //Defines the calculation of modules of each field.
    public function generateModulesCalcField()
    {
        //Defines the module for calculating the digit verifier
        $this->digitableNumber->setModuleCalcField(1, 10);
        $this->digitableNumber->setModuleCalcField(2, 10);
        $this->digitableNumber->setModuleCalcField(3, 10);
    }
    
   /*
    *
    * This function is an abstract declaration on parent class, needed to generate the barcode
    * If you wish, the parent class has a method called "barCodeFixedValues" that implements rules of
    * barcode fixed values based on FEBRABAN defaults. See more at parent function on "include" path
    * ATTENTION: This function needs return a string containing length 25 and only numbers to process 
    *            the information correctly
    * @params: As you wish, by default, the sabStruct object
    * @return: (String) String with length 25
    */
    public function generateBarCode(sabStruct $sabStruct)
    {
        $product = 2;
        $constant1 = 1;
        $bankAccount = substr($sabStruct->getTransferorBankAccount(), -4,4);
        $transferorCode = substr($sabStruct->getTransferorCode(), -7,7);
        $invoiceNumber = $sabStruct->getInvoiceOurNumber();
        $constant2 = 40;
        $campolivre = $product . $constant1 . $bankAccount . $transferorCode . $invoiceNumber . $constant2;

        //Gera��o dos digitos verificadores.
        $constant3 = $this->modulo10($campolivre, 2, true);
        $constant4 = $this->modulo11Banrisul($campolivre . $constant3, 2, 7);

        while( $this->mod == 1 )
        {
            $constant3 = $constant3+1;
            if( $constant3 == 10 )
            {
                $constant3 = 0;
            }
            $constant4 = $this->modulo11Banrisul($campolivre . $constant3, 2, 7);
        }

        $this->barCodeDataFixedValuesWithFactor($sabStruct);
        $this->barCodeData->setBarCodeField('product'       , $product                                             ,  1, 0);
        $this->barCodeData->setBarCodeField('constant1'     , $constant1                                           ,  1, 0);
        $this->barCodeData->setBarCodeField('bankAccount'   , $bankAccount                                         ,  4, 0);
        $this->barCodeData->setBarCodeField('transferorCode', $transferorCode                                      ,  7, 0);
        $this->barCodeData->setBarCodeField('invoiceNumber' , $invoiceNumber                                       ,  8, 0);
        $this->barCodeData->setBarCodeField('constant2'     , $constant2                                           ,  2, 0);
        $this->barCodeData->setBarCodeField('constant3'     , $constant3                                           ,  1, 0);
        $this->barCodeData->setBarCodeField('constant4'     , $constant4                                           ,  1, 0);
        $this->barCodeData->setBarCodeField('barCodeDV'     , $this->modulo11(self::onlyNumbers($this->barCodeData->returnBarCode())),  1, 0);
    }
    
    public function modulo11Banrisul($num, $factor = 2, $factorMax = 9)
    {
        $totalX  = 0;
        $value   = array();
        $factor_ = $factor;
        for ( $x = strlen($num); $x > 0; $x-- )
        {
            $pos       = substr($num, $x-1, 1);
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

        if ( $totalX < 11 )
        {
            $mod = $totalX;
        }
        else
        {
            $mod = $totalX % 11;
        }

        $this->mod = $mod;       
        
        if ( $mod == 0 )
        {
            return $mod;
        }
        else
        {
           return 11 - $mod;
        }
    }
}
?>
