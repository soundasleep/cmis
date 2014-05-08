Drupal CMIS
===========

This is a port of the original [Drupal CMIS project](https://drupal.org/project/cmis) with some additional fixes.

### Installation

Right now you should just be able to drop this directly into an existing Drupal installation to replace the CMIS module with no ill effects. Not tested.

Make sure that you also have the `cmis-phplib` library installed into your `sites/all/libraries/cmis-phplib` directory.

### Feature changes

* _CMIS Check_ link is actually visible in _Configure_ menu
* Content field type `text_textfield` [can be synced](https://drupal.org/node/2074063#comment-7797843)

### Developer changes

* Uses [EditorConfig](http://editorconfig.org) for consistent whitespace throughout

### Original project

The original project Git: http://git.drupal.org/project/cmis.git
