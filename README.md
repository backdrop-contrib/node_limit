Node Limit Module
======================

This module allows administrators to limit the number of nodes that users may create.  This limitation may be done based on a number of conditions, including placing limits on a per-role or per-user basis.

Requirements
------------
This module has no other requirements or dependencies.

Installation
------------
- Install and enable the primary **node_limit** module using the official [Backdrop CMS modules installation instructions](https://docs.backdropcms.org/documentation/extend-with-modules).
- The core Node Limit framework adds additional functionality that limits how many nodes may be created by your users. Each of the submodules below add a different condition to your Limit definition. These conditions may be combined to restrict the number of nodes that can be created in a precise way. Activate one or more of these submodules based on what type of limit you would like to use. These are:
  - **node_limit_interval module** - This submodule provides the ability to place a limit on the number of nodes that can be created within a certain amount of time. After tha time interval has past, the user may create another node.
  - **node_limit_role** - Activate this submodule to add the ability to restrict the amount of nodes that all users in a given role may create.
  - **node_limit_type** - The *node_limit_type* module allow you to restrict the amount of nodes of a given type that may be created overall within a site.
  - **node_limit_user** - Limitations can be put on how many nodes that a specific individual user can create by activating the *node_limit_user* module.
  - **node_limit_userofrole** -This module limits the amount of nodes that can be created by each user of a given role.

How to use this module
------------
Once you have enabled the Node Limit module and any of the submodules for the type of Limits you want, visit the configuration page under Administration > Structure > Node Limit > Settings (admin/structure/node_limit/settings) to configure the module.

By default, users will be shown an 'Access Denied' page when they exceed the number of nodes that they are allowed to create. The message that will be shown is set in the Global Message field. If you want to redirect the user to a custom error page when they attempt to exceed their limit, enter the path to that error page in the Global Redirect Path field.

These messages can be even more granular, with custom error text and error page paths set on a per-content-type basis. You can activate this feature by checking the box labeled 'Enable custom error message'.

You can get started by creating your first Node Limit! You can do this by clicking on the 'Add Node Limit' tab. In the form, define the new Node Limit with a Description and numeric Limit on how many nodes can be created and check the boxes of the type of
conditions you want the Node Limit to use.

Once added, the Limit will be added to the List and takes effect immediately.

**Note:**
- Node limits do not apply to user 1.
- Only users with the "administer node limits" permission will be able to edit node limits.
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

