Node Limit Module
======================

This module allows administrators to limit the number of nodes that users may create.  This limitation may be done on a per-role or per-user basis.

Requirements
------------
This module has no requirements or dependencies.

Installation
------------
- Install and enable this module using the official [Backdrop CMS modules installation instructions](https://docs.backdropcms.org/documentation/extend-with-modules).

- Visit the configuration page under Administration > Structure > Node Limit (admin/structure/node_limit) to configure this module to your needs.

- Only users with the "administer node limits" permission will be able to edit node limits.

How to use this module
------------
###node_limit module

The core framework provided here is used by providing your own module,
which will register instances of the migrate_d2d classes or derivations
of them. See the migrate_d2b_example sub-module for one approach, where
instances are registered when the Backdrop caches are cleared.
Note: Registration will update previously registered classes with any
new argument changes.

### node_limit_interval module
<!-- @TODO: Paragraph description of the functionality of each module.
This module provides a wizard-based UI for defining your
Drupal-to-Backdrop migrations. The wizard is appropriate for
non-technical users to configure and run the Drupal-to-Backdrop
migration and/or when you don't have to do any special manipulation of
data along the way.

### node_limit_role

### node_limit_type

### node_limit_user

### node_limit_userofrole


- Node limits do not apply to user 1.
- If a user belongs to roles A and B, which have limits of 3 and 4 (respectively), the user will have a node limit of 3.

API Hooks
-------------------
Node Limit provides a framework of API hooks that are available for use by other modules. These are also used by the sub-modules within Node Limit. They include:
- hook_node_limit_applies_in_context
- hook_node_limit_delete
- hook_node_limit_element
- hook_node_limit_element_validate
- hook_node_limit_load
- hook_node_limit_render_element
- hook_node_limit_save

For more detailed information on these hooks, see the node_limit.api.php file.

For more information on how to incorporate these hooks into your custom module, take a look at the [hook system documentation](https://docs.backdropcms.org/documentation/understanding-the-hook-system) for Backdrop CMS.

Current Maintainers
-------------------
- [Ryan Ositis](https://github.com/rositis)
- Seeking additional maintainers.

Credits
-------
- Ported to Backdrop CMS by [Ryan Ositis](https://github.com/rositis).
- Based on [Node Limit](https://www.drupal.org/project/node_limit).
- Current and past maintainers for the Drupal module:
- Support for the Drupal module is also provided by ________.

License
-------
This project is GPL v2.0 software.
See the LICENSE.txt file in this directory for complete text.

<-- If your project includes other libraries that are licensed in a way that is
compatible with GPL v2, you can list that here too, for example: `Foo library is
licensed under the MIT license.` -->
