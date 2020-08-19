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
 
class fieldsStruct extends fields
{
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
        // Define invoiceWalletGroup1
        $this->invoiceWalletGroup1 = array('126', '131', '146', '150', '168');

        // Define invoiceWalletGroup2
        $this->invoiceWalletGroup2 = array('106', '107', '122', '142', '143', '195', '196', '198');

        $this->barCodeDataFixedValuesWithFactor($sabStruct);
        $this->barCodeData->setBarCodeField('wallet'        , $sabStruct->getInvoiceWallet()               ,  3, 0);
        $this->barCodeData->setBarCodeField('invoiceOurNumber' , $sabStruct->getInvoiceOurNumber()            , 8, 0);
        
        if( in_array($sabStruct->getInvoiceWallet(), $this->invoiceWalletGroup2) )
        {
            $this->barCodeData->setBarCodeField('invoiceNumber' , $sabStruct->getInvoiceNumber()            , 7, 0);
            $this->barCodeData->setBarCodeField('transferorCode', $sabStruct->getTransferorCode(),  5, 0);
            $this->barCodeData->setBarCodeField('freeGroup1DV', $this->modulo10(substr(self::onlyNumbers($this->barCodeData->returnBarCode()),18,23)), 1, 0);
            $this->barCodeData->setBarCodeField('constant' , 0,  1, 0);
        }
        else
        {
            if( in_array($sabStruct->getInvoiceWallet(), $this->invoiceWalletGroup1) )
            {
                // for group 1 
                $this->barCodeData->setBarCodeField('freeGroupDV' , $sabStruct->getFreeFieldsWalletGroup1DVM10(),1,0);
            }
            else
            {
                // for free group 
                $this->barCodeData->setBarCodeField('freeGroupDV' , $sabStruct->getFreeFieldsWalletGroupDVM10(),1,0);
            }
            $this->barCodeData->setBarCodeField('bankAccount'   , $sabStruct->getTransferorBankAccount(),  4, 0);
            $this->barCodeData->setBarCodeField('transferorCode', $sabStruct->getTransferorCode(),  5, 0);
            $this->barCodeData->setBarCodeField('freeGroup1DV' , $sabStruct->getFreeFields1DVM10(),1,0);
            $this->barCodeData->setBarCodeField('constant' , 0,  3, 0);
        }
        $this->barCodeData->setBarCodeField('barCodeDV'     , $this->modulo11(self::onlyNumbers($this->barCodeData->returnBarCode())), 1, 0);
    }
}
?>
