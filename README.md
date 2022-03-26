Node Limit Module
======================

This module allows administrators to limit the number of nodes that users may create.  This limitation may be done on a per-role or per-user basis.

Requirements
------------
This module has no other requirements or dependencies.

Installation
------------
- Install and enable this module using the official [Backdrop CMS modules installation instructions](https://docs.backdropcms.org/documentation/extend-with-modules).

- Visit the configuration page under Administration > Structure > Node Limit (admin/structure/node_limit) to configure this module to your needs.

- Only users with the "administer node limits" permission will be able to edit node limits.

How to use this module
------------
### node_limit module

The core Node Limit framework adds additional functionality that limits how many nodes may be created by your users. Each of the submodules below add a different condition to your Limit definition. These conditions may be combined to restrict the number of nodes that can be created in a precise way.

### node_limit_interval module
This submodule provides the ability to place a limit on the number of nodes that can be created withing a certain amount of time.

### node_limit_role
Activate this submodule to add the ability to restrict the amount of nodes that all users in a given role may create.

### node_limit_type
The *node_limit_type* module allow you to restrict the amount of nodes of a given type that may be created by a user.

### node_limit_user
Limitations can be put on how many nodes that a specific individual user can create by activating the *node_limit_user* module.

### node_limit_userofrole
This module limits the amount of nodes that can be created by each user of a given role.

**Note:**
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

For more detailed information on these hooks, see the *node_limit.api.php* file.

For more information on how to incorporate these hooks into your custom module, take a look at the [hook system documentation](https://docs.backdropcms.org/documentation/understanding-the-hook-system) for Backdrop CMS.

Current Maintainers
-------------------
- [Ryan Ositis](https://github.com/rositis)
- Seeking additional maintainers.

Credits
-------
- Ported to Backdrop CMS by [Ryan Ositis](https://github.com/rositis).
- Based on [Node Limit](https://www.drupal.org/project/node_limit) for Drupal 7.
- Current and past maintainers for the Drupal module:
  - [Edouard Cunibil (DuaelFr)](https://www.drupal.org/u/duaelfr)
  - [davedelong](https://www.drupal.org/u/davedelong)
  - [Marco Vito Moscaritolo (mavimo)](https://www.drupal.org/u/mavimo)
  - [Keyral (keyral)](https://www.drupal.org/u/keyral)
  - [Neeraj Kumar (neerajskydiver)](https://www.drupal.org/u/neerajskydiver)
  - [Adrian Cid Almaguer (adriancid)](https://www.drupal.org/u/adriancid)

License
-------
This project is GPL v2.0 software.
See the LICENSE.txt file in this directory for complete text.

