"""
    add SS, CN
    add storage

"""

# Import the Portal object.
import geni.portal as portal
# Import the ProtoGENI library.
import geni.rspec.pg as pg
# Emulab specific extensions.
import geni.rspec.emulab as emulab

# Create a portal context.
pc = portal.Context()

# Describe the parameter this profile script can accept
pc.defineParameter("n", "Number of Storage Server", portal.ParameterType.INTEGER, 1)
pc.defineParameter("m", "Number of Computing Node", portal.ParameterType.INTEGER, 1)
pc.defineParameter("t", "Type of machines", portal.ParameterType.STRING,"c220g1",[("c220g1","Wisconsin c220g1"),("c220g2","Wisconsin c220g2"),("d430","Emulab d430")])

# Retrieve the values the user specifies during instantiation
params = pc.bindParameters()

# Create a Request object to start building the RSpec.
rspec = pg.Request()

# Create a link with the type of LAN.
link = pg.LAN("lan")


#disk_image="urn:publicid:IDN+emulab.net+image+emulab-ops:UBUNTU16-64-STD"
#disk_image="urn:publicid:IDN+apt.emulab.net+image+cloudincr-PG0:TTU-OpenHPC-CN"

# Storage Serve
for i in range (params.n):
    node = pg.RawPC("server"+str(i))
    node.hardware_type = params.t
    #node.disk_image=disk_image_lustre
    node.installRootKeys(True, True)
    #bs = node.Blockstore("bss"+str(i), "/mydata")
    #bs.size = "60GB"
    #node.addService(install)
    #node.addService(execute)
           
  #  node.disk_image=disk_image
    iface = node.addInterface("if"+str(i))
    link.addInterface(iface)
    rspec.addResource(node)


# Computing Node
for i in range (params.m):
    node = pg.RawPC("node"+str(i))
    node.hardware_type = params.t
    #node.disk_image=disk_image_cn
    node.installRootKeys(True, True)
    #bs = node.Blockstore("bsc"+str(i), "/mydata")
    #bs.size = "60GB"
    #node.addService(install)
    #node.addService(execute)
                           
   # node.disk_image=disk_image
    network_index = i + params.n
    iface = node.addInterface("if"+str(network_index))
    link.addInterface(iface)
    rspec.addResource(node)  


rspec.addResource(link)

# Print the RSpec to the enclosing page.
pc.printRequestRSpec(rspec)
