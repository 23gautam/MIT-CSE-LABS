from django.contrib import admin
from django.urls import path,include
from . import views

urlpatterns=[
    path('',views.home,name="home"),
    path('fill',views.fill,name='fill'),
    path('add',views.add,name='add'),
    path('display',views.display,name='display'),
    path('product/<int:product_id>/',views.product_detail,name="product_detail")
]