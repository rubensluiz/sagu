<?php
$MIOLO->logMessage('[LOGIN] file:'.$_SERVER['SCRIPT_NAME']);
$MIOLO->logMessage('[LOGIN] Using login prompt');
$ui = $MIOLO->getUI();
$theme->clearContent();
$navbar->addOption('Login', $module, 'login');
$login = $auth->getLogin();
$return_to = MIOLO::_REQUEST('return_to');
$module = 'basico';


// If the user is logged in, send to the start up module
if ($login && ($return_to == ''))
{
   //$form = $ui->getForm($module,'frmAccess',$login);
   $MIOLO->invokeHandler($MIOLO->getConf('options.basico'), 'main');
}
else
{
   $form = $ui->getForm($module,'frmLogin');
}
if ($theme->getContent()  == '')
{
   $theme->insertContent($form);
}
?>
