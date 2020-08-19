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
        $this->digitableNumber->setModuleCalcField(4, 10);
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
        $this->barCodeDataFixedValuesWithFactor($sabStruct);

        if ( (strlen($sabStruct->getTransferorAgreement()) == 4) && (strlen($sabStruct->getTransferorComplement()) == 7) )
        {
            $this->barCodeData->setBarCodeField('transferorAgreement'  , $sabStruct->getTransferorAgreement()  , 4, 0);
            $this->barCodeData->setBarCodeField('transferorComplement' , $sabStruct->getTransferorComplement() , 7, 0);
            $this->barCodeData->setBarCodeField('TransferorBankAccount', $sabStruct->getTransferorBankAccount(), 4, 0);
            $this->barCodeData->setBarCodeField('transferorCode'       , $sabStruct->getTransferorCode()       , 8, 0);
            $this->barCodeData->setBarCodeField('wallet'               , $sabStruct->getInvoiceWallet()        , 2, 0);
            $this->barCodeData->setBarCodeField('barCodeDV', $this->modulo11(self::onlyNumbers($this->barCodeData->returnBarCode())), 1, 0);
        }
        elseif ( (strlen($sabStruct->getTransferorAgreement()) == 6) && (strlen($sabStruct->getTransferorComplement()) == 5) && (strlen($sabStruct->getTransferorCode()) > 0) )
        {
            $this->barCodeData->setBarCodeField('transferorAgreement'  , $sabStruct->getTransferorAgreement()  , 6, 0);
            $this->barCodeData->setBarCodeField('transferorComplement' , $sabStruct->getTransferorComplement() , 5, 0);
            $this->barCodeData->setBarCodeField('TransferorBankAccount', $sabStruct->getTransferorBankAccount(), 4, 0);
            $this->barCodeData->setBarCodeField('transferorCode'       , $sabStruct->getTransferorCode()       , 8, 0);
            $this->barCodeData->setBarCodeField('wallet'               , $sabStruct->getInvoiceWallet()        , 2, 0);
            $this->barCodeData->setBarCodeField('barCodeDV', $this->modulo11(self::onlyNumbers($this->barCodeData->returnBarCode())), 1, 0);
        }
        elseif ( (strlen($sabStruct->getTransferorAgreement()) == 7) && (strlen($sabStruct->getTransferorComplement()) == 10) )
        {
            $this->barCodeData->setBarCodeField('constantZero'        , 0                                     ,  6, 0);
            $this->barCodeData->setBarCodeField('transferorAgreement' , $sabStruct->getTransferorAgreement()  ,  7, 0);
            $this->barCodeData->setBarCodeField('transferorComplement', $sabStruct->getTransferorComplement() , 10, 0);
            $this->barCodeData->setBarCodeField('wallet'              , $sabStruct->getInvoiceWallet()        ,  2, 0);
            $this->barCodeData->setBarCodeField('barCodeDV', $this->modulo11(self::onlyNumbers($this->barCodeData->returnBarCode())), 1, 0);
        }
        elseif ( (strlen($sabStruct->getTransferorAgreement()) == 6) && (strlen($sabStruct->getTransferorComplement()) == 17) )
        {
            $this->barCodeData->setBarCodeField('transferorAgreement' , $sabStruct->getTransferorAgreement()  ,  6, 0);
            $this->barCodeData->setBarCodeField('transferorComplement', $sabStruct->getTransferorComplement() , 17, 0);
            $this->barCodeData->setBarCodeField('wallet'              , $sabStruct->getInvoiceWallet()        ,  2, 0);
            $this->barCodeData->setBarCodeField('barCodeDV'           , $this->modulo11(self::onlyNumbers($this->barCodeData->returnBarCode())), 1, 0);
        }
    }
}
?>
