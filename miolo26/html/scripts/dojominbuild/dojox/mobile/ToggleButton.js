//>>built
define("dojox/mobile/ToggleButton",["dojo/_base/declare","dojo/dom-class","dijit/form/_ToggleButtonMixin","./Button"],function(a,b,c,d){return a("dojox.mobile.ToggleButton",[d,c],{baseClass:"mblToggleButton",_setCheckedAttr:function(){this.inherited(arguments);var a=(this.baseClass+" "+this["class"]).replace(/(\S+)\s*/g,"$1Checked ").split(" ");b[this.checked?"add":"remove"](this.focusNode||this.domNode,a)}})});
//# sourceMappingURL=ToggleButton.js.map