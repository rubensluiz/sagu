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
 * This class Main file for sub project sab of sagu2
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
 * */
/**
 * Main file for sub project sab of sagu2
 *
 * @author William Prigol Lopes [william@solis.coop.br]
 *
 * @version $Id$
 *
 * \b Maintainers: \n
 * Alexandre Heitor Schmidt [alexsmith@solis.coop.br]
 * Armando Taffarel Neto [taffarel@solis.coop.br]
 * Leovan Tavares da Silva [leovan@solis.coop.br]
 * Samuel Koch [samuel@solis.coop.br]
 * William Prigol Lopes [william@solis.coop.br]
 *
 * @since
 * Class created on 22/02/2008
 *
 * \b Organization: \n
 * SOLIS - Cooperativa de Solucoes Livres \n
 * The SAGU Development Team
 *
 * \b Copyright: \n
 * Copyright (c) 2008 SOLIS - Cooperativa de Solucoes Livres \n
 *
 * \b License: \n
 * Licensed under GPLv2 (for further details read the COPYING file or http://www.gnu.org/licenses/gpl.html )
 *
 * \b History: \n
 * See: http://sagu.solis.coop.br
 *
 * */
include('include/core.php');

class sab
{
    public $sabStruct;
    public $fieldsStruct;
    private $sabLayout;
    private $isOnline;
    /**
     * @var (char) Defined as in fpdf output types
     */
    private $outputType = 'I';
    /**
     * @var (string) Name of the file which will hold the generation data
     */
    private $fileName = 'boleto.pdf';


    /*
     * Function to construct the object
     *
     * @params $bankId (varchar): Bank identification to call the correct layout, if exists
     *
     * @returns: Nothing if all run correctly, or the error message if something goes wrong
     *
     */
    public function __construct( $bankId, $isOnline, $sabDirectory )
    {
        $this->isOnline = $isOnline;
        if ( !$sabDirectory )
        {
            $this->errors[] = _('Por favor, verifique a configura��o do sistema, o caminho para o sistema de automa��o da fatura n�o foi encontrado');
            return false;
        }
        else
        {
            if ( !$this->isOnline )
            {
                $layoutFile = $sabDirectory . '/layouts/l' . $bankId . '/layout.php';
                $fieldsFile = $sabDirectory . '/layouts/l' . $bankId . '/fields.php';
            }
            else
            {
                $layoutFile = $sabDirectory . '/layouts/l' . $bankId . '/layoutOnline.php';
                $fieldsFile = $sabDirectory . '/layouts/l' . $bankId . '/fieldsOnline.php';
            }
        }
        if ( (file_exists( $layoutFile )) && (file_exists( $fieldsFile )) )
        {
            if ( $this->isOnline )
            {
                try
                {
                    include_once('layouts/l' . $bankId . '/layoutOnline.php');
                    include_once('layouts/l' . $bankId . '/fieldsOnline.php');
                    $this->sabStruct = new sabStructOnline();

                    return true;
                }
                catch ( exception $e )
                {
                    $this->errors[] = _('Falha ao definir a configura��o do layout online');
                    throw new Exception( _('Falha ao carregar os arquivos do layout online') );

                    return false;
                }
            }
            else
            {
                try
                {
                    include_once('layouts/l' . $bankId . '/layout.php');
                    include_once('layouts/l' . $bankId . '/fields.php');
                    $this->sabStruct = new sabStruct();

                    return true;
                }
                catch ( exception $e )
                {
                    $this->errors[] = _('Falha ao definir a configura��o do layout');
                    throw new Exception( _('Falha ao carregar os arquivos do layout') );

                    return false;
                }
            }
        }
        else
        {
            $this->errors[] = _('Layout para o banco ') . $bankId . _(' n�o foi encontrado. Os arquivos ') . $layoutFile . _(' e ') . $fieldsFile . _(' devem existir.');

            return false;
        }
    }
    /*
     * Function called to generate the layout and make some final adjusts to create and normalize information to invoice
     * @params: No parameters needed
     * @returns: True if ok, otherwise false (for more details see getError() function)
     */

    public function generate($download = true)
    {
        if ( !$this->isOnline )
        {
            $this->sabStruct->normalizeValues();
            if ( $this->sabStruct->checkRequiredFields() )
            {
                $this->fieldsStruct = new fieldsStruct( $this->sabStruct );
                $layout = new sabLayout( $this->sabStruct, $this->fieldsStruct );
                $layout->setFileName( $this->fileName );
                
                if ( $download )
                {
                    $layout->setOutputType( $this->outputType );
                }
                else
                {
                    $layout->clearOutputType();
                }
                
                $layout->generate();

                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            // Retorno o link
            return $this->sabStruct->generateLink();
        }
    }
    /*
     * Return the error descriptions
     * @param: $outType S: Screen, A: Array
     * @returns: (array): Return on screen or in array the errors
     */

    public function getErrors()
    {
        if ( is_array( $this->sabStruct->errors ) )
        {
            return $this->sabStruct->errors;
        }
        if ( is_array( $this->fieldsStruct->errors ) )
        {
            return $this->fieldsStruct->errors;
        }
        if ( is_array( $this->errors ) )
        {
            return $this->errors;
        }
    }

    /**
     * @return the $outputType
     */
    public function getOutputType()
    {
        return $this->outputType;
    }

    /**
     * @return the $fileName
     */
    public function getFileName()
    {
        return $this->fileName;
    }

    /**
     * Obt�m o c�digo de barras
     * @return the $barCodeNumber
     */
    public function getBarCodeNumber()
    {
        $this->sabStruct->normalizeValues();
        if ( $this->sabStruct->checkRequiredFields() )
        {
            $fieldsStruct = new fieldsStruct( $this->sabStruct );
            $barCodeNumber = $fieldsStruct->getBarCodeNumber();
        }

        return $barCodeNumber;
    }

    /**
     * Obt�m o n�mero digitavel
     * @return the $digitableNumber
     */
    public function getDigitableNumber()
    {
        $this->sabStruct->normalizeValues();
        if ( $this->sabStruct->checkRequiredFields() )
        {
            $fieldsStruct = new fieldsStruct( $this->sabStruct );
            $digitableNumber = $fieldsStruct->getDigitableNumber();
        }

        return $digitableNumber;
    }

    /**
     * @param $outputType the $outputType to set
     */
    public function setOutputType( $outputType )
    {
        $this->outputType = $outputType;
    }

    /**
     * @param $fileName the $fileName to set
     */
    public function setFileName( $fileName )
    {
        $this->fileName = $fileName;
    }
}
?>
