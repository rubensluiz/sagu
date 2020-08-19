<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of Matricula
 *
 * @author jonasrosa
 */
class MatriculaTest extends WebDriverTestCase
{

    public function testMatricula ()
    {
        $this->driver->get ($this->url . '/miolo20/html/index.php?module=academic&action=main:process:enrollContract');
        $this->lookUp ('m_contractPersonId', array('personName' => 'va%'), 'VANISE MANZZINI FRAGA');

        $this->clickButton ('btnNext');
    }

    public function testMatriculaDebito ()
    {
        $this->driver->get ($this->url . '/miolo20/html/index.php?module=academic&action=main:process:enrollContract');
        $this->lookUp ('m_contractPersonId', array('personName' => 'va%'), 'VANISE MANZZINI FRAGA');

        $this->clickButton ('btnNext');

        $message = utf8_encode ("O sistema n�o retornou a mensagem esperada!");

        if (!$actual = $this->driver->findElement (WebDriverBy::cssSelector ('div.m-prompt-box-text ul li'))->getText ())
        {
            WebDriverException::throwException (15, $message, '');
        } else
        {
            $expected = utf8_encode ('O sistema detectou um d�bito financeiro em atraso com a institui��o. Clique aqui para consultar este d�bito.');
            $this->assertEquals ($expected, $actual);
        }
    }

}

?>
