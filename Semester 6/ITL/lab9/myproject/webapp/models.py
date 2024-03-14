from django.db import models
from sqlite3 import Timestamp
from turtle import title

# Create your models here.
from django import forms 


class BlogPost(models.Model):
    title= models.CharField(max_length=150)
    body = models.TextField()
    timestamp = models.DateTimeField()
    
    
class Meta:
    ordering = ('-timestamp',)
    
class BlogPostForm(forms.ModelForm):
    model = BlogPost
    exclude = ('timestamp',) 